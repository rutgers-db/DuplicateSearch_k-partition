#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <binary_file_name>" << endl;
        return 1;
    }

    string binFileName = argv[1];
    vector<vector<int>> docs;

    try {
        loadBin(binFileName, docs);
    } catch (const char* msg) {
        cerr << msg << endl;
        return 1;
    }

    long long totalTokens = 0;
    for (const auto& doc : docs) {
        totalTokens += doc.size();
    }

    int numDocuments = docs.size();
    double avgTokensPerDoc = numDocuments > 0 ? static_cast<double>(totalTokens) / numDocuments : 0;

    cout << "Total number of tokens: " << totalTokens << endl;
    cout << "Number of documents: " << numDocuments << endl;
    cout << "Average number of tokens per document: " << avgTokensPerDoc << endl;

    return 0;
}
