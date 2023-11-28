#!/bin/bash
rm ExpResults/Exp_CW_generation.txt
rm ExpResults/Exp_CW_generation_baseline.txt
dataset=('/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/openwebtext_gpt2.bin' '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/pile_gpt2.bin' '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/PAN11_external_source.bin')

for i in 0 1 2
do
    echo ${dataset[i]}
    for n in 100
    do
        echo n=${n}
        for len in 100 1000 10000 100000
        do
            echo len=${len}
            for k in 16 32 64 128 256
            do
                loop=1
                while(( $loop>0 ))
                do
                    let loop--
                    echo ./a.out -f ${dataset[i]} -n ${n} -k ${k} -l ${len}
                    echo ./base.out -f ${dataset[i]} -n ${n} -k ${k} -l ${len}
                    ./a.out -f ${dataset[i]} -n ${n} -k ${k} -l ${len} >> ExpResults/Exp_CW_generation.txt
                    ./base.out -f ${dataset[i]} -n ${n} -k ${k} -l ${len} >> ExpResults/Exp_CW_generation_baseline.txt
                done
            done
        done
    done
done