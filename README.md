# Near-Duplicate Sequence Alignment with One Permutation Hashing

This repository contains the implementation for Near-Duplicate Sequence Alignment using One Permutation Hashing (OPH). It is designed to efficiently index and search for near-duplicate sequences in large datasets.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

Before you begin, ensure you have the following installed:
- CMake
- A C++ compiler

### Installation

Clone the repository and build the project using the following commands:

```bash
cd build
cmake ..
make
```

### Usage
Once you have built the project and compiled all the executables, you can start using the tools for indexing and searching.

### Building an Index
To build an index of Minhash (KMINS or OPH), you can use the following command for KMINS(or OPH) index as an example:

./build/KMINS_build -f /path/to/dataset.bin -i /path/to/index_file.data -k 2 -l 0 -o /path/to/output.txt

Command Line Arguments
The program accepts the following command line arguments:

- `-f`: Source file path
- `-i`: Index file path
- `-k`: Sketch size
- `-l`: Longest (optional)
- `-t`: Threshold
- `-q`: Number of queries
- `-o`: KMINS or OPH (optional)
- `-m`: Method (optional)


### Near Duplicate Sequence Searching

After building the index, you can perform near-duplicate sequence searches using the following command:
```bash
./build/main -f /path/to/dataset.bin -n 1000 -q 1 -i /path/to/query_sequences.bin
```

Command Line Arguments for Searching
The search command accepts the following arguments:

- `-f`: Source file path
- `-i`: Index file path
- `-k`: Sketch size
- `-l`: Longest (optional)
- `-t`: Threshold
- `-q`: Number of queries
- `-o`: KMINS or OPH (optional)
- `-m`: Method (optional)

Example usage:
```bash
./build/main -f bin_file_path -k k [-l longest] -t threshold -q query_num [-o KMINSorOPH] [-m method]
```
