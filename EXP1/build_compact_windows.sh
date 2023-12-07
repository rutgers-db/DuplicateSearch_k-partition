#!/bin/bash
dataset=('/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/PAN11_external_source.bin')
index_path=('/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/index/PAN11_external_source')

for method in 'OPH' 'KMINS'
do
    for k in 16 32 64 128 256
    do
        for n in 100
        do
            l=0
            for i in 0
            do
                index_file=${index_path[i]}_${method}_n${n}_k${k}_l${l}.data
                out_file=${index_path[i]}_${method}_n${n}_k${k}_l${l}.txt
                echo ./${method}_build -f ${dataset[i]} -i ${index_file} -n ${n} -k ${k} -l ${l} -o ${out_file}
                ./${method}_build -f ${dataset[i]} -i ${index_file} -n ${n} -k ${k} -l ${l} -o ${out_file}
            done
        done
    done
done