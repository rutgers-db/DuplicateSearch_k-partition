#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

// load the vector<int> of a bin file and push back to docs
void loadBin(const string &binFileName, vector<int> &vec) {
    ifstream ifs(binFileName, ios::binary);
    if (!ifs) {
        cout << "error open bin file" << endl;
        return;
    }
    int size;
    ifs.read((char *)&size, sizeof(int));
    vec.resize(size);
    ifs.read((char *)&vec[0], sizeof(int) * size);
    ifs.close();
}

void loadBin(const string &binFileName, vector<vector<int>> &docs) {
    ifstream ifs(binFileName, ios::binary);
    if (!ifs) {
        cout << "Error open bin file" << endl;
        throw "Error open bin file";
    }
    int size;
    while (ifs.read((char *)&size, sizeof(int))) {
        vector<int> vec(size);
        ifs.read((char *)&vec[0], sizeof(int) * size);
        docs.emplace_back(vec);
    }
    ifs.close();
    cout << "From Binary File " << binFileName << " read " << docs.size() << " documents" << endl;    
}

/**
 * Reads pairs of integers from a file where each line contains a pair.
 * 
 * The expected file format is as follows:
 * Each line in the file should contain exactly two integers separated by a comma and a space.
 * For example:
 *   1, 100
 *   2, 200
 *   3, 300
 * 
 * @param file_path The path to the file containing the pairs.
 * @return A vector of pairs, where each pair is read from a line in the file.
 */
std::vector<std::pair<int, int>> read_pairs_from_file(const std::string& file_path) {
    std::vector<std::pair<int, int>> pairs; // Vector to store the pairs
    std::ifstream file(file_path);          // Open the file at the given path
    std::string line;                       // String to store each line from the file
    int first, second;                      // Integers to store the parsed pair from each line

    // Read the file line by line
    while (std::getline(file, line)) {
        std::stringstream ss(line);         // Use stringstream for parsing the line

        // Parse the line into two integers, separated by a comma and space
        if (ss >> first && ss.ignore() >> second) {
            pairs.emplace_back(first, second); // Add the parsed pair to the vector
        }
    }

    return pairs; // Return the vector of pairs
}