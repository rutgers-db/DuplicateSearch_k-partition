#!/bin/bash
rm ExpResults/Exp_CW_query.txt
rm ExpResults/Exp_CW_query_baseline.txt
dataset=('/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/openwebtext_gpt2.bin' '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/pile_gpt2.bin' '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/PAN11_external_source.bin')

queryNum=10
l=1000000
for k in 16 32 64 128 256
do
    for n in 10
    do
        for i in 0 1 2
        do
            for theta in  0.5 0.6 0.7 0.8 0.9 1
            do
                loop=1
                while(( $loop>0 ))
                do
                    let loop--
                    echo ./OPH_longest_filter -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum}
                    # echo ./OPH -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum}
                    echo ./KMINS_INTERVAL_SCAN_filter -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum}
                    # echo ./KMINS -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum}
                    ./OPH_longest_filter -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum}
                    # ./OPH -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum} >> ExpResults/Exp_CW_query.txt
                    ./KMINS_INTERVAL_SCAN_filter -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum}
                    # ./KMINS -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum} >> ExpResults/Exp_CW_query_baseline.txt
                done
            done
        done
    done
done