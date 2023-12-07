#!/bin/bash
dataset=('/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/PAN11_external_suspicious.bin')
index_path=('/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/index/PAN11_external_source')

qn=100
for method in 'OPH' 'KMINS'
do
    for k in 16 32 64 128 256
    do
        for n in 100
        do
            l=0
            for i in 0
            do
                for theta in 0.5 0.6 0.7 0.8 0.9 1.0
                do
                    for m in 0 1
                    do
                        index_file=${index_path[i]}_${method}_n${n}_k${k}_l${l}.data
                        out_file=${index_path[i]}_${method}_n${n}_k${k}_l${l}_t${theta}_m${m}.txt
                        echo ./${method} -f ${dataset[i]} -i ${index_file} -t ${theta} -q ${qn} -m ${m} -o ${out_file}
                        ./${method} -f ${dataset[i]} -i ${index_file} -t ${theta} -q ${qn} -m ${m} -o ${out_file}
                    done
                done
            done
        done
    done
done