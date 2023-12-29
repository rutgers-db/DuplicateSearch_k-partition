# Build Query Dataset of Openwebtext and Pile

## Overview
This project is designed to create a query dataset from the Openwebtext and Pile datasets. It focuses on identifying and recording texts that match specific criteria within the first 10,000,000 documents of each dataset.

Pile: /research/projects/zp128/SelfGenerationText/gpt-neo-540L_50TOPK_2_7B.bin
Openwebtext: /research/projects/zp128/SelfGenerationText/gpt2-medium-540L_50TOPK_400000S.bin

## Logic Flow
The process for building the query dataset involves several key steps:

1. **Index Building**: Construct an index for the first 10,000,000 documents of each dataset (Openwebtext and Pile).

2. **Search Generation Texts**: Load generation texts from a specified directory and search each text against the created index.

3. **Record Matches**: Identify and record documents where matches are found.

4. **Sorting Results**: Sort the matched texts based on the number of results, prioritizing texts with a larger number of matches.

5. **Data Writing**: Write the sorted texts into a binary file and record each text's corresponding text ID.

## Output
The project generates two primary outputs:

1. **Query Binary File**: A binary file named `matched_generation_{dataset}.bin`, containing the sorted query data.

2. **Log File**: A log file that records the corresponding text ID for each query.

## Usage
