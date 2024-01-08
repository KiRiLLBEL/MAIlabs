import subprocess
for i in range(1, 11):
    test_file = f"test{i}.txt"
    output_main_file = "output_main.txt"
    output_test_file = "output_test.txt"
    subprocess.run(f"./main < {test_file} >> {output_main_file}", shell=True)
    subprocess.run(f"./test < {test_file} >> {output_test_file}", shell=True)
    print(f"test{i} complete")