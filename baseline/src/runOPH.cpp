#include "./util/util.hpp"
#include "./util/IO.hpp"
#include "./util/Hasher.hpp"
#include "./MINHASH/oph.hpp"
#include <omp.h>

using namespace std;

string output_file;
double threshold = 0.5;
string dataset = "PAN";
int queryNum = __INT_MAX__;
int k = 64;
int tokenNum = 50257;
bool if_intervalscan = true;
bool if_longest = true;
int main(int argc, char *argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "q:t:o:k:i:l:d:")) != EOF)
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
        case 'k':
            k = stoi(optarg);
            break;
        case 'i':
            if_intervalscan = stoi(optarg);
            break;
        case 'l':
            if_longest = stoi(optarg);
            break;
        case 'd':
            dataset = optarg;
            break;
        }
    }
    string pair_file_path, source_file_path, query_file_path;
    if (dataset == "PAN")
    {
        pair_file_path = "/path/to/your/sample_source_sus_pairs.txt";
        source_file_path = "/path/to/your/all_source_with_plagiarism.bin";
        query_file_path = "/path/to/your/all_suspicious_seqs_pan11.bin";
    }
    if (dataset == "OWT")
    {
        pair_file_path = "/path/to/your/OWT/random_pairs.txt";
        source_file_path = "/path/to/your/OWT/sample_OWT_200.bin";
        query_file_path = "/path/to/your/OWT/OWT_sampleWins_200.bin";
    }
    if (dataset == "WIKI")
    {
        pair_file_path = "/path/to/your/WIKI/random_pairs.txt";
        source_file_path = "/path/to/your/WIKI/sample_wiki_200.bin";
        query_file_path = "/path/to/your/WIKI/Wiki_sampleWins_200.bin";
    }

#ifdef ARIBITRARY_GEN
    cout << "Arbitirarily Generate" << endl;
#endif
    if (if_longest)
        cout << "Longest Searching" << endl;

    // the pair is <source_id, suspicious id>
    auto pairs = read_pairs_from_file(pair_file_path);
    vector<vector<int>> query, source;
    loadBin(query_file_path, query);
    loadBin(source_file_path, source);

    // open the result output file
    ofstream output_file_stream(output_file);
    stringstream buffer; // Create a stringstream for buffering

    queryNum = min(queryNum, (int)pairs.size());
    double ave_timeCost[128] = {0};
    double ave_[128] = {0};
    unsigned int CWSNum[128] = {0};
    size_t results_num[128] = {0};
    Hasher hasher(k);
#pragma omp parallel for
    for (int i = 0; i < queryNum; i++)
    {
        auto tid = omp_get_thread_num();
        auto &pair = pairs[i];
        auto &s_seq = source[pair.first];
        auto &q_seq = query[pair.second];
        OPH oph(q_seq, s_seq, k, threshold, hasher, tokenNum);
        oph.init();
        auto time_st = timerStart();
        CWSNum[tid] += oph.run(if_intervalscan, if_longest);
        ave_timeCost[tid] += timerCheck(time_st);
        results_num[tid] += oph.result.size();
        // auto res = oph.filter_covered_ranges();
        // Write the vector<pair<int,int>> res into the output file stream in one line

        // for (const auto &pair : res)
        // {
        //     buffer << "(" << pair.first << "," << pair.second << ") ";
        // }
        // buffer << endl;
    }
    double timeCost = 0;
    double ave_cws = 0;
    double total_results_num = 0;

    for (int i = 0; i < 128; i++){
        ave_cws += CWSNum[i];
        timeCost += ave_timeCost[i];
        total_results_num += results_num[i];

    }
    timeCost /= queryNum;
    ave_cws /= queryNum;
    total_results_num /= queryNum;

    string method_name = if_intervalscan == true ? "IntervalScan" : "SegmentTree";
    cout << "Average Time cost of" << method_name << " is " << timeCost << endl;
    cout << "Average CWS of" << method_name << " is " << ave_cws << endl;
    cout << "Average results num of" << method_name << " is " << total_results_num << endl;
    output_file_stream << buffer.str();
    output_file_stream.close();
}