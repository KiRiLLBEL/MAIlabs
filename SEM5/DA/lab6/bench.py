def run_programs():
    import subprocess
    for i in range(1, 101):
        test_file = f"tests/test_{i}.txt"
        output_main_file = "output_main.txt"
        output_test_file = "output_test.txt"
        subprocess.run(f"./main < {test_file} >> {output_main_file}", shell=True)
        subprocess.run(f"./test < {test_file} >> {output_test_file}", shell=True)
run_programs()