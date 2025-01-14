#!/bin/bash

dataset=(
    '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/openwebtext_gpt2.bin'
    '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/PAN11_external_source.bin'
    '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/wiki40b_en_train_gpt2.bin'
)

for file in "${dataset[@]}"; do
    ./calData "$file" >> data_log.txt
done
