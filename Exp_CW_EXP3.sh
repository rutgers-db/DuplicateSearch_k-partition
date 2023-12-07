#!/bin/bash
rm ExpResults/Exp_CW_query.txt
rm ExpResults/Exp_CW_query_baseline.txt
dataset=('/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/openwebtext_gpt2.bin' '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/pile_gpt2.bin' '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/PAN11_external_source.bin')

queryNum=20
for k in 32 64 128
do
    for n in 100000
    do
        for i in 0 1 2
        do
            for theta in  0.6 0.8 1
            do
                echo ./OPH_longest_filter -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum}
                echo ./OPH -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum}
                echo ./KMINS_INTERVAL_SCAN_filter -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum}
                echo ./KMINS -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum}
                ./OPH_longest_filter -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum}
                ./OPH -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum}
                ./KMINS_INTERVAL_SCAN_filter -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum}
                ./KMINS -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum}
            done
        done
    done
done