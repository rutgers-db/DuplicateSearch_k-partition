#include <string>
#include <vector>
#include <fstream>

using namespace std;

void loadBin(const string &binFileName, vector<vector<int>> &docs) {
    ifstream ifs(binFileName, ios::binary);
    if (!ifs) {
        cout << "error open bin file" << endl;
        return;
    }
    int size;
    int limit = 10, num = 0;
    while (ifs.read((char *)&size, sizeof(int))) {
        vector<int> vec(size);
        ifs.read((char *)&vec[0], sizeof(int) * size);
        docs.emplace_back(vec);
        printf("Binary File %s Read, whose has %d texts\n", binFileName.c_str(), size);
        if (++num == limit)
            break;
    }
    ifs.close();
}