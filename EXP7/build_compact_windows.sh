#!/bin/bash
dataset=('/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/openwebtext_gpt2.bin' '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/PAN11_external_source.bin' '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/wiki40b_en_train_gpt2.bin')
index_path=('/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/index0/openwebtext_gpt2' '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/index0/PAN11_external_source' '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/index0/wiki40b_en_train_gpt2')

for method in 'OPH' 'KMINS'
do
    for k in 16 32 64 128 256
    do
        for n in 100
        do
            for l in 100 1000 10000 100000
            do
                for i in 0 1 2
                do
                    index_file=${index_path[i]}_${method}_n${n}_k${k}_l${l}.data
                    out_file=${index_path[i]}_${method}_n${n}_k${k}_l${l}.txt
                    echo ./${method}_build -f ${dataset[i]} -i ${index_file} -n ${n} -k ${k} -l ${l} -o ${out_file}
                    ./${method}_build -f ${dataset[i]} -i ${index_file} -n ${n} -k ${k} -l ${l} -o ${out_file}
                done
            done
        done
    done
done