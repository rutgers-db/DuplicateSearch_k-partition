#!/bin/bash
rm ExpResults/Exp_CW_query.txt
rm ExpResults/Exp_CW_query_baseline.txt
dataset=('/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/openwebtext_gpt2.bin' '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/pile_gpt2.bin' '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/PAN11_external_source.bin')

queryNum=10
l=1000000
for i in 0 1 2
do
    echo ${dataset[i]}
    for n in 10
    do
        echo n=${n}
        for theta in  0.5 0.6 0.7 0.8 0.9 1
        do
            echo theta=${theta}
            for k in 16 32 64 128 256
            do
                loop=1
                while(( $loop>0 ))
                do
                    let loop--
                    echo ./OPH_longest -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum}
                    # echo ./OPH -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum}
                    # echo ./KMINS -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum}
                    ./OPH_longest -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum}
                    # ./OPH -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum} >> ExpResults/Exp_CW_query.txt
                    # ./KMINS -f ${dataset[i]} -n ${n} -k ${k} -l ${l} -t ${theta} -q ${queryNum} >> ExpResults/Exp_CW_query_baseline.txt
                done
            done
        done
    done
done