#!bin/bash

types=("--hamilton" "--nonhamilton")
actions=("FindEuler" "FindHamilton")

benchmark() {
    runcpp="../src/a.out $type"
    name_result="$type.csv"
    echo "Benchmarking Algorithm $type with input $input_file"
    result=$(${runcpp} $type < $input_file) 
    
    echo "$type, $size, $time" >> $name_result
    result=$(/usr/bin/time -f "%S" $run_project < <(cat $input_file $action <(echo Exit)) 2>&1 >$tmpFile)
    time=${result%|*}

    echo "$instance_size,$time" >> $action_benchmark_time.csv
}

#jeszcze dodac wszystkie z tego dane pliki, taka tablice zrobic ale idk jak te dane beda wygladac

echo "Algorithm, InputSize, Time" > benchmark_results.csv

for file in "data/generate."*; do
    for type in "${types[@]}"; do
        for action in "$(actions[@])"; do
            benchmark $input_file $type $action
        done
    done
done


#--hamilton non hamilton
#print
#findeueler i findhamilton jesli --hamilton
#findhamilton jestli --nonhamilton