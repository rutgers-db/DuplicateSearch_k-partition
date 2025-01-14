#include "../src/SEF/SeedExtension.hpp"
#include "../src/BF/BruteForce.hpp"
#include "../src/util/IO.hpp"
#include "../src/util/util.hpp"
#include "../src/util/Hasher.hpp"
#include "../src/MINHASH/kmins.hpp"
#include "../src/Faerie/Faerie.hpp"
using namespace std;

int main(){
    const string query_bin_file = "/research/projects/zp128/OPH_Align/Dataset_Construction/PAN11/data/all_suspicious_seqs_pan11.bin";
    const string source_bin_file = "/research/projects/zp128/OPH_Align/Dataset_Construction/PAN11/data/all_source_with_plagiarism.bin";
    const int source_id = 7397;
    const int query_id = 30085;
    
    vector<vector<int>> query_seqs;
    loadBin(query_bin_file, query_seqs);
    vector<vector<int>> docs;
    loadBin(source_bin_file, docs);

    auto sef_st = timerStart();
    // BruteForce bf(query_seqs[query_id], docs[source_id], 0.5);
    // bf.run();
    
    // cout<<jaccard_similarity(query_seqs[query_id], vector<int>(docs[source_id].begin(), docs[source_id].begin() + 1067));
    // auto res = bf.filterOverlappingRanges();
    Faerie faerie(query_seqs[query_id], docs[source_id], 0.5);
    faerie.run();
    auto res = faerie.filter_covered_ranges();
    for(auto pair: res){
        cout<< "(" << pair.first << "," << pair.second << ") ";
    }
    printf("This pair cost%f\n", timerCheck(sef_st));
}