#!bin/bash

types=("--hamilton" "--nonhamilton")
actions=("FindEuler" "FindHamilton")

benchmark() {
    runcpp="../src/a.out $type"
    name_result="$type.csv"
    echo "Benchmarking Algorithm $action with input $input_file" 
    
    echo "$type, $size, $time" >> $name_result
    if [[ ($type == "--nonhamilton" && $action == "FindHamilton") || $type == "--hamilton" ]] 
    then
        result=$(/usr/bin/time -f "%S" $runcpp < <(cat $input_file <(echo $action) <(echo Exit)) 2>&1 >$tmpFile)
    fi
    time=${result%|*}

    echo "$instance_size,$time" >> $action_benchmark_time.csv
}



echo "InputSize, Time" > $action_benchmark_time.csv

for input_file in "data/generate"*; do
    for type in "${types[@]}"; do

        for action in "${actions[@]}"; do

            benchmark $input_file $type $action
        done
    done
done
