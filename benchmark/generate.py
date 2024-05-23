import os
import shutil
import sys

graph_types = ["hamilton", "nonhamilton"]

def generate_file(filename, n, saturation, type):
    with open(filename, 'w') as file:
        if(type == "hamilton"):
            file.write(f"{n}\n{saturation}\n")
        elif(type == "nonhamilton"):
            file.write(f"{n}\n")

if __name__ == "__main__":

    if len(sys.argv) != 3:
        print("Usage: python generate.py <start_exponent> <end_exponent>")
        sys.exit(1)
    try:
        start_exponent = int(sys.argv[1])
        end_exponent = int(sys.argv[2])
    except ValueError as e:
        print(f"Error: {e}")
        print("Usage: python generate.py <start_exponent> <end_exponent>")
        sys.exit(1)

    # Directory where files will be saved
    directory = 'data'

    # Clear the contents of the benchmark directory
    if os.path.exists(directory):
        shutil.rmtree(directory)
    os.makedirs(directory)

    max_n_length = len(str(2 ** end_exponent))  # Determine the length of the largest n
    for t in graph_types:
        for i in range(start_exponent, end_exponent + 1):
            if(t == "hamilton"):
                saturation = 30
                filename = os.path.join(directory, f"generate{i}_{t}{saturation}.txt")
                generate_file(filename, i, 30,t)
                saturation = 70
                filename = os.path.join(directory, f"generate{i}_{t}{saturation}.txt")
                generate_file(filename, i, 70, t)
            elif(t == "nonhamilton"):
                saturation = 50
                filename = os.path.join(directory, f"generate{i}_{t}{saturation}.txt")
                generate_file(filename, i, 50, t)
