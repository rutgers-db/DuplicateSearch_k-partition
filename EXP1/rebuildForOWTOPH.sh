#!/bin/bash
#SBATCH --output=./build_sample_OPH.txt
#SBATCH --mem=200g

dataset=('/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/sample_OWT.bin')
index_path=('/research/projects/zp128/OPH_Align/Dataset_Construction/Owt/tmp/tmp_indexOPH_2.bin')

for method in 'OPH'
do
    for k in 4 8 16 32 64
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