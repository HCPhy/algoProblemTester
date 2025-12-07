import os
import sys
import argparse
import textwrap
import google.generativeai as genai

def generate_problem(api_key, topic):
    """
    Generates a C++ algorithm problem and solution using Gemini.
    """
    genai.configure(api_key=api_key)
    model = genai.GenerativeModel('gemini-2.0-flash-exp') 

    prompt = f"""
    You are an expert algorithm problem creator. Create a coding problem based on the topic: "{topic}".
    
    Output THREE distinct parts separated by "---SECTION_DELIMITER---".
    
    PART 1: The Problem Description (Markdown).
    - clear problem statement.
    - Input/Output format.
    - Constraints.
    
    PART 2: The Reference Solution (C++ Code).
    - Provide a complete, correct C++ function.
    - The function MUST use standard library types (std::vector, std::string, etc).
    - Do NOT include `main()` function.
    - Include necessary headers (e.g., <vector>, <algorithm>).
    - The function signature should be: `inline [ReturnType] ref_solution([Args])`.
    
    PART 3: The User Skeleton (C++ Code).
    - Same signature as the reference solution but named `user_solution`.
    - Empty body or return dummy value.
    - Include necessary headers.
    
    Do NOT include markdown code fences (```cpp, ```) in PART 2 and PART 3. Just raw code.
    """

    print(f"Generating problem for topic: '{topic}'...")
    try:
        response = model.generate_content(prompt)
        content = response.text
        
        parts = content.split("---SECTION_DELIMITER---")
        if len(parts) != 3:
            print("Error: LLM output format incorrect. Retrying or check prompt.")
            # For robustness, we could retry here, but let's just fail for now.
            print("Raw response preview:", content[:200])
            return False

        problem_md = parts[0].strip()
        ref_cpp = parts[1].strip()
        user_skeleton_cpp = parts[2].strip()
        
        # Clean up possible markdown fences if the model ignored instructions
        def clean_code(code):
            lines = code.splitlines()
            if lines and lines[0].strip().startswith("```"): lines = lines[1:]
            if lines and lines[-1].strip().startswith("```"): lines = lines[:-1]
            return "\n".join(lines)

        ref_cpp = clean_code(ref_cpp)
        user_skeleton_cpp = clean_code(user_skeleton_cpp)

        # Write to files
        base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        src_dir = os.path.join(base_dir, "src")
        
        with open(os.path.join(base_dir, "current_problem.md"), "w") as f:
            f.write(problem_md)
            
        with open(os.path.join(src_dir, "ref_sol.cpp"), "w") as f:
            f.write(ref_cpp)
            
        with open(os.path.join(src_dir, "user_sol.cpp"), "w") as f:
            f.write(user_skeleton_cpp)
            
        print("Success!")
        print(f"Problem description saved to: {os.path.join(base_dir, 'current_problem.md')}")
        print(f"Reference solution saved to: {os.path.join(src_dir, 'ref_sol.cpp')}")
        print(f"User skeleton saved to: {os.path.join(src_dir, 'user_sol.cpp')}")
        
        return True

    except Exception as e:
        print(f"API Error: {e}")
        return False

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate Algorithm Problem")
    parser.add_argument("topic", nargs="?", help="Description of the problem to generate", default="Sort a vector of integers")
    parser.add_argument("--key", help="Gemini API Key", default=os.environ.get("GEMINI_API_KEY"))
    
    args = parser.parse_args()
    
    if not args.key:
        print("Error: GEMINI_API_KEY not found in environment variables and not provided via --key.")
        sys.exit(1)
        
    generate_problem(args.key, args.topic)
