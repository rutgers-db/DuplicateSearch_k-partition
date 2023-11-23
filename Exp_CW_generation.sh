dataset=('/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/openwebtext_gpt2.bin' '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/pile_gpt2.bin' '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/PAN11_external_suspicious.bin')

for i in 0 1 2
do
    echo ${dataset[i]}
    for n in 100 1000
    do
        echo n=${n}
        for len in 100 1000 10000 100000
        do
            echo len=${len}
            for k in 16 32 64
            do
                loop=10
                while(( $loop>0 ))
                do
                    let loop--
                    ./a.out -f ${dataset[i]} -n ${n} -k ${n} -l ${len} >> Exp_CW_generation.txt
                done
            done
        done
    done

    
done