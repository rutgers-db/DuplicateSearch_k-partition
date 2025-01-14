#!/bin/bash
#SBATCH --output=/research/projects/zp128/OPH_Align/Dataset_Construction/Owt/log/build_WIKI_KMINS.txt
#SBATCH --mem=500g

dataset=('/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/sample_wiki.bin')
index_path=('/research/projects/zp128/OPH_Align/Dataset_Construction/Owt/tmp/tmp_index_kmins_1.bin')

for method in 'KMINS'
do
    for k in 1 2 4 8 16
    do
        l=0
        for i in 0
        do
            index_file=${index_path[i]}_${method}_n${n}_k${k}_l${l}.data
            out_file=${index_path[i]}_${method}_n${n}_k${k}_l${l}.txt
            echo ./${method}_build -f ${dataset[i]} -i ${index_file} -k ${k} -l ${l} -o ${out_file}
            ./${method}_build -f ${dataset[i]} -i ${index_file} -k ${k} -l ${l} -o ${out_file}
        done
    done
done