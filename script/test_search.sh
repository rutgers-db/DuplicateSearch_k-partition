#!/bin/bash
#SBATCH --output=/research/projects/zp128/OPH_Align/Dataset_Construction/Owt/log/test_search.txt
#SBATCH --mem=100g
query_file='/research/projects/zp128/OPH_Align/Dataset_Construction/Owt/test/test_query.bin' 
index_path='/research/projects/zp128/OPH_Align/Dataset_Construction/Owt/index/openwebtext_k64Smallindex.bin'

k=64
thres=0.7
QueryNum=100;
echo /research/projects/zp128/OPH_Align/Dataset_Construction/Owt/build/main -f ${query_file} -i ${index_path} -k ${k} -t ${thres} -q ${QueryNum}

/usr/bin/time -v /research/projects/zp128/OPH_Align/Dataset_Construction/Owt/build/main -f ${query_file} -i ${index_path} -k ${k} -t ${thres} -q ${QueryNum}