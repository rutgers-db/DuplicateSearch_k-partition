#!/bin/bash -l
#SBATCH --output=log/build_index.txt
#SBATCH --mem=500g
dataset=('/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/openwebtext_gpt2.bin' '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/pile_gpt2.bin')
index_path='/research/projects/zp128/OPH_Align/Dataset_Construction/Owt/index/pile_index.bin'

INTERVAL_LIMIT=100
Doc_Num=0
k=32

echo /research/projects/zp128/OPH_Align/Dataset_Construction/Owt/build/build -f ${dataset[0]} -n ${Doc_Num} -i ${index_path} -k ${k} -L ${INTERVAL_LIMIT}

/research/projects/zp128/OPH_Align/Dataset_Construction/Owt/build/build -f ${dataset[1]} -n ${Doc_Num} -i ${index_path} -k ${k} -L ${INTERVAL_LIMIT}