#include "util/util.hpp"
#include "./util/IO.hpp"
#include "./SEF/SeedExtension.hpp"

using namespace std;

string output_file;
double threshold = 0.5;
int queryNum = __INT_MAX__;
int main(int argc, char *argv[]){
    int opt;
    while ((opt = getopt(argc, argv, "q:t:o:")) != EOF)
    {
        switch (opt)
        {
        case 'q':
            queryNum = stoi(optarg);
            break;
        case 't':
            threshold = stof(optarg);
            break;
        case 'o':
            output_file = optarg;
            break;
        }
    }
    
    const string pair_file_path = "/path/to/your/data/sample_source_sus_pairs.txt";
    const string source_file_path = "/path/to/your/data/all_source_with_plagiarism.bin";
    const string query_file_path = "/path/to/your/data/all_suspicious_seqs_pan11.bin";
    
    // the pair is <source_id, suspicious id>
    auto pairs = read_pairs_from_file(pair_file_path);
    vector<vector<int>> query, source;
    loadBin(query_file_path, query);
    loadBin(source_file_path, source);

    // open the result output file
    ofstream output_file_stream(output_file);

    queryNum = min(queryNum, (int)pairs.size());
    double ave_timeCost = 0;
    for(int i = 0; i < queryNum; i++){
        auto & pair = pairs[i];
        auto time_st = timerStart();
        auto & s_seq = source[pair.first];
        auto & q_seq = query[pair.second];
        SeedExtension seed_ext(q_seq, s_seq, 1, threshold);
        seed_ext.init();
        auto res = seed_ext.run();
        ave_timeCost += timerCheck(time_st);
        // Write the vector<pair<int,int>> res into the output file stream in one line
        for (const auto& pair : res) {
            output_file_stream << "(" << pair.first << "," << pair.second << ") ";
        }
        output_file_stream << endl;
    }
    ave_timeCost/=queryNum;
    cout<<"Average Time cost is "<<ave_timeCost<<endl;
    output_file_stream.close();
}