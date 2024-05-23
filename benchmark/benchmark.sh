#!bin/bash

types=("--hamilton" "--nonHamilton")
actions=("FindEuler" "FindHamilton")

benchmark() {
    tmpFile=$(mktemp)
    runcpp="../src/a.out $type"
    if [[ ($type == "--nonHamilton" && $action == "FindHamilton") || $type == "--hamilton" ]] 
    then
        echo "Benchmarking Algorithm $action with input $input_file" 
        result=$(/usr/bin/time -f "%S" $runcpp < <(cat $input_file <(echo $action) <(echo Exit)) 2>&1 >/dev/null)
        time=${result%|*}
        result_file_name=$(echo $action)Time.csv
        echo "$instance_size,$time" >> $result_file_name
    fi
}

for input_file in "data/generate"*; do
    instance_size=$(echo $input_file | cut -c $((${#input_file}-1))-$((${#input_file})))
    echo $instance_size
    for type in "${types[@]}"; do
        if [[ $input_file =~ "$(echo $type | cut -c 3-)" ]]
            then
            for action in "${actions[@]}"; do
                benchmark $input_file $type $action $instance_size
            done
        fi
    done
done
