import os
import shutil
import sys

graph_types = ["hamilton", "nonHamilton"]

def generate_file(filename, n, saturation, type):
    with open(filename, 'w') as file:
        if(type == "hamilton"):
            file.write(f"{n} {saturation}\n")
        elif(type == "nonHamilton"):
            file.write(f"{n}\n")

if __name__ == "__main__":

    if len(sys.argv) != 5:
        print("Usage: python generate.py <start_exponent> <end_exponent>")
        sys.exit(1)
    try:
        start1 = int(sys.argv[1])
        end1 = int(sys.argv[2])
        exp_start = int(sys.argv[3])
        exp = int(sys.argv[4])
    except ValueError as e:
        print(f"Error: {e}")
        print("Usage: python generate.py <start_exponent> <end_exponent>")
        sys.exit(1)

    # Directory where files will be saved
    directories = ['hamiltonian', 'non_hamiltonian']

    # Clear the contents of the benchmark directory
    for directory in directories:
        if os.path.exists(directory):
            shutil.rmtree(directory)
        os.makedirs(directory)
        if(directory == 'non_hamiltonian'):
            end = end1
            start = start1
        else:
            start = exp_start
            end = exp
        for i in range(start, end + 1):
            if(directory == 'hamiltonian'):
                j = 2**i 
                if j < 10:
                    N = "0"+str(j)
                else:
                    N = str(j)
                t = "hamilton"
                end
                saturation = 30
                filename = os.path.join(directory, f"generate_{saturation}{t}{N}")
                generate_file(filename, j, 30,t)
                saturation = 70
                filename = os.path.join(directory, f"generate_{saturation}{t}{N}")
                generate_file(filename, j, 70, t)
            elif(directory == 'non_hamiltonian'):
                if i < 10:
                    N = "0"+str(i)
                else:
                    N = str(i)
                t = "nonHamilton"
                saturation = 50
                filename = os.path.join(directory, f"generate_{t}{N}")
                generate_file(filename, i, 50, t)