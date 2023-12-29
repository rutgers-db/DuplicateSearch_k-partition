#!/bin/bash
#SBATCH --output=log/build_index.txt
#SBATCH --mem=500g
INTERVAL_LIMIT=100
Doc_Num=100 #if Doc_Num as 0, it will index the whole dataset 4000000
k=64

index_path='./test_query.bin'
dataset=('/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/openwebtext_gpt2.bin' '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/pile_gpt2.bin')

echo /research/projects/zp128/OPH_Align/Dataset_Construction/Owt/test/getQuery -f ${dataset[0]} -n ${Doc_Num} -i ${index_path} -k ${k} -L ${INTERVAL_LIMIT}

/research/projects/zp128/OPH_Align/Dataset_Construction/Owt/test/getQuery -f ${dataset[0]} -n ${Doc_Num} -i ${index_path} -k ${k} -L ${INTERVAL_LIMIT}