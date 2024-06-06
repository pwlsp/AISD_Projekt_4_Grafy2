#!bin/bash
blue=$(tput setaf 4)
gray=$(tput setaf 7)
green=$(tput setaf 2)
teal=$(tput setaf 6)
normal=$(tput sgr0)

actions=("FindEuler") #"FindHamilton") 
file_types=("hamiltonian") # "non_hamiltonian")

benchmark() {
    tmpLogFile=$(mktemp)
    cat > $tmpLogFile <<EOF
    $normal============================[INSTANCE SIZE $instance_size]============================$green
Benchmarking Algorithm $action with input $input_file
$normal============================[Input]============================$gray
$(cat $input_file <(echo $action) <(echo Exit))
$normal============================[Program Output]===================$teal 

EOF

    printf "$(more $tmpLogFile)" #printf allows for pretty colors
    tmpFile=$(mktemp) #saving to tmp file so it can be logged in follow up log
    runcpp="../src/a.out $type"
    echo
   
    result=$(/usr/bin/time -f "%S%M" $runcpp < <(cat $input_file <(echo $action) <(echo Exit)) 2>&1 >$tmpFile)
    #echo $(cat $tmpFile)
    time=$(cat $tmpFile | tr ' ' '\n' | grep Time*)
    time=$(echo $time | cut -c 5-${#time})
    type_result=$(echo $type | cut -c 3-${#type})
    result_file_name=$(echo "$action")Time.csv
    echo "$type_result,$instance_size,$time" >> $result_file_name

    cat > $tmpLogFile <<EOF

$(cat $tmpFile)
$normal============================[usr/bin/time]=====================$green
time = $(echo $time) milliseconds 
Saved to $result_file_name

$normal
EOF
        printf "$(more $tmpLogFile)" #printf allows for pretty colors

}


for file_type in ${file_types[@]}; do
    for input_file in "$file_type/generate"*; do
        instance_size=$(echo $input_file)
        if [[ $file_type == "hamiltonian" ]]
        then
            instance_size=$(echo $instance_size | cut -c 32-${#instance_size})
            type="--hamilton"
                for action in "${actions[@]}"; do
                    benchmark $input_file $type $action $instance_size
                done
        elif [[ $file_type == "non_hamiltonian" ]]
        then
            instance_size=$(echo $instance_size | cut -c 37-${#instance_size})
            type="--non-hamilton"
            action="FindHamilton"
            benchmark $input_file $type $action $instance_size
        fi
    done
    echo >> $result_file_name
done

