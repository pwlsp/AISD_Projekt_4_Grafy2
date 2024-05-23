#!bin/bash

types=("--hamilton" "--nonhamilton")

benchmark() {
    runcpp="../src/a.out"
    name_result="$type.csv"
    echo "Benchmarking Algorithm $type with input $input_file"
    result=$(${runcpp} $type < $input_file) 
    #pierwsza linijka to czy jest czy nie ma i druga to czas, musze pomyslec jaki bedzie output dokladnie
    if [[ $($type | cut -c 1-2) == "hamilton" ]]
    then
        
    else

    fi
    size=$(cat $input_file | head -n -1)
    echo "$type, $size, $time" >> $name_result
}

#jeszcze dodac wszystkie z tego dane pliki, taka tablice zrobic ale idk jak te dane beda wygladac

echo "Algorithm, InputSize, Time" > benchmark_results.csv

for file in "${input_files[@]}"; do
    for type in "${types[@]}"; do
        benchmark $input_file $type
    done
done


#--hamilton non hamilton
#print
#findeueler i findhamilton jesli --hamilton
#findhamilton jestli --nonhamilton