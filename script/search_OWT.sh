#!/bin/bash
#SBATCH --output=/research/projects/zp128/OPH_Align/Dataset_Construction/Owt/log/bsearch_omp_2.txt
#SBATCH --mem=300g
query_file='/research/projects/zp128/SelfGenerationText/gpt2-medium-540L_50TOPK_400000S.bin' 
index_path='/research/projects/zp128/OPH_Align/Dataset_Construction/Owt/index/openwebtext_k64fullindex.bin'

k=64
thres=0.7
QueryNum=100;
echo /research/projects/zp128/OPH_Align/Dataset_Construction/Owt/build/main -f ${query_file} -i ${index_path} -k ${k} -t ${thres} -q ${QueryNum}

/usr/bin/time -v /research/projects/zp128/OPH_Align/Dataset_Construction/Owt/build/main -f ${query_file} -i ${index_path} -k ${k} -t ${thres} -q ${QueryNum}