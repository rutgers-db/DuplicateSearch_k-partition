#!/bin/bash
rm ExpResults/Exp_CW_query.txt
rm ExpResults/Exp_CW_query_baseline.txt
dataset=('/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/openwebtext_gpt2.bin' '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/pile_gpt2.bin' '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/PAN11_external_source.bin')

queryNum=100
for n in 10000 100000 1000000
do
    for k in 32 64 128
    do
        for i in 0 1 2
        do
            for theta in 0.7 0.9
            do
                echo ./OPH_longest_filter -f ${dataset[i]} -n ${n} -k ${k} -t ${theta} -q ${queryNum}
                ./OPH_longest_filter -f ${dataset[i]} -n ${n} -k ${k} -t ${theta} -q ${queryNum}
            done
        done
    done
done