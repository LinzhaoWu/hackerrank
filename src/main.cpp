#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <deque>
#include <cstring>
#include <string>
#include <queue>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <map>
#include <unordered_map>
#include <list>
#include <climits>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);


#define OTHERS

#ifdef OTHERS
class TrieNode {
  public:
    unordered_map<char, TrieNode*> children = {};
    vector<pair<int, unsigned long>> scores = vector<pair<int, unsigned long>>();
    
    ~TrieNode() {
        this->destroy_tree();
    }
    
    unsigned long get_score(int first, int last) {
        unsigned long score = 0;
        for (pair<int, unsigned long> s : scores) {
            if (s.first > last) {    // guaranteed increasing order
                return score;
            }
            if (s.first >= first) {
                score += s.second;
            }
        }
        return score;
    }
    
    TrieNode* get_child(char c) {
        if (this->children.find(c) != this->children.end()) {
            return this->children[c];
        }
        return nullptr;
    }
    
    TrieNode* add_child(char c) {
        if (this->children.find(c) == this->children.end()) {
            children[c] = new TrieNode();
        }
        return this->children[c];
    }
    
  private:
    void destroy_tree() {
        for (auto [c, child] : children) {
            delete child;
        }
    }
};



unsigned long get_score(TrieNode* root, string dna, int first, int last) {
    unsigned long score = 0;
    for (size_t i = 0; i < dna.size(); ++i) {
        TrieNode* node = root;
        size_t j = i;
        while (node != nullptr && j < dna.size()) {
            node = node->get_child(dna[j]);
            if (node != nullptr) {
                score += node->get_score(first, last);
            }
            ++j;
        }
    }
    return score;
}

int main() {
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string genes_temp_temp;
    getline(cin, genes_temp_temp);

    vector<string> genes_temp = split(rtrim(genes_temp_temp));

    vector<string> genes(n);

    for (int i = 0; i < n; i++) {
        string genes_item = genes_temp[i];

        genes[i] = genes_item;
    }

    string health_temp_temp;
    getline(cin, health_temp_temp);

    vector<string> health_temp = split(rtrim(health_temp_temp));

    vector<int> health(n);

    for (int i = 0; i < n; i++) {
        int health_item = stoi(health_temp[i]);

        health[i] = health_item;
    }

    TrieNode root;
    string s_temp;
    getline(cin, s_temp);

    int s = stoi(ltrim(rtrim(s_temp)));

    if (s == 0 || n == 0) {
        cout << "0 0" << endl;
        return 0;
    }
    unsigned long best_score = 0;
    unsigned long worst_score = ULONG_MAX;
    for (int s_itr = 0; s_itr < s; s_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int first = stoi(first_multiple_input[0]);
        int last = stoi(first_multiple_input[1]);
        string dna = first_multiple_input[2];
        
        unsigned long score = get_score(&root, dna, first, last);
        best_score = max(best_score, score);
        worst_score = min(worst_score, score);
    }

    fprintf(fptr, "%d %d\n", worst_score, best_score);
    fclose(fptr);

    return 0;
}

#else
uint64_t process(const vector<string> &genes, const vector<int> &health, 
             int first, int last, string_view dna_strand)
{
    uint64_t iRet = 0;
    for (int i(first); i <= last; i++) {
        string_view sv = genes[i];
        auto pos = dna_strand.find(sv);
        while (pos != string_view::npos)
        {
            iRet += health[i];
            pos = dna_strand.find(sv, pos + 1);
        }
        
    }
    return iRet;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string genes_temp_temp;
    getline(cin, genes_temp_temp);

    vector<string> genes_temp = split(rtrim(genes_temp_temp));

    vector<string> genes(n);

    for (int i = 0; i < n; i++) {
        string genes_item = genes_temp[i];

        genes[i] = genes_item;
    }

    string health_temp_temp;
    getline(cin, health_temp_temp);

    vector<string> health_temp = split(rtrim(health_temp_temp));

    vector<int> health(n);

    for (int i = 0; i < n; i++) {
        int health_item = stoi(health_temp[i]);

        health[i] = health_item;
    }

    string s_temp;
    getline(cin, s_temp);

    int s = stoi(ltrim(rtrim(s_temp)));

    uint64_t iMax = 0, iMin = UINT64_MAX;

    for (int s_itr = 0; s_itr < s; s_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int first = stoi(first_multiple_input[0]);

        int last = stoi(first_multiple_input[1]);

        string d = first_multiple_input[2];

        uint64_t value = process(genes, health, first, last, d);
        iMax = max(iMax, value);
        iMin = min(iMin, value);
    }

    fprintf(fptr, "%d %d\n", iMin, iMax);
    fclose(fptr);

    return 0;
}

#endif

string ltrim(const string &str) {
    string s(str);

    return s;
}

string rtrim(const string &str) {
    string s(str);

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}