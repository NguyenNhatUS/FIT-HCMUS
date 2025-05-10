#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<math.h>
#include<string>

using namespace std; 

struct Company {
    string name;
    string profit_tax;
    string address;
};

struct HashTable {
    Company hashTable[2000];
};

const int MOD = 2000;

vector<Company> readCompanyList(string filename) {
    vector<Company> company;
    ifstream fin(filename);
    string line;
    getline(fin,line);
    while(getline(fin,line)) {
        if(line.empty()) continue;
        Company tmp;
        stringstream ss(line);
        string token;
        getline(ss,token,'|');
        tmp.name = token;
        getline(ss,token,'|');
        tmp.profit_tax = token;
        getline(ss,token,'|');
        tmp.address = token;
        company.push_back(tmp);
    }
    fin.close();
    return company;
}

long long hashString(string company_name) {
    const int p = 31;
    const long int m = 2000;
    long long p_pow = 1;
    long long hashResult = 0;
    string s;
    if(company_name.size() <= 20) {
        s = company_name;
    }
    else {
        s = company_name.substr(company_name.size() - 20);
    }
    for (char c : s) {
        int val = int(c);
        hashResult = (hashResult + val * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hashResult;
}

HashTable* createHashTable(vector<Company> list_company) {
    HashTable* hashing = new HashTable;
    for(int i = 0;i < 2000;i++) {
        hashing->hashTable[i].name = "";
        hashing->hashTable[i].profit_tax = "";
        hashing->hashTable[i].address = "";
    }
    int n = list_company.size();
    for(int i = 0;i < n;i++) {
        int cnt = 0;
        long long hashValue = hashString(list_company[i].name);
        while(hashing->hashTable[(hashValue + cnt) % MOD].name != "") {
            cnt++;
        }
        hashing->hashTable[(hashValue + cnt) % MOD].name = list_company[i].name;
        hashing->hashTable[(hashValue + cnt) % MOD].profit_tax = list_company[i].profit_tax;
        hashing->hashTable[(hashValue + cnt) % MOD].address = list_company[i].address;
    }
    return hashing;
}

void insert(HashTable* hash_table, Company company) {
    int hashValue = hashString(company.name);
    int cnt = 0;
    while(hash_table->hashTable[(hashValue + cnt) % MOD].name != "") {
        cnt++;
    }
    hash_table->hashTable[(hashValue + cnt) % MOD].name = company.name;
    hash_table->hashTable[(hashValue + cnt) % MOD].profit_tax = company.profit_tax;
    hash_table->hashTable[(hashValue + cnt) % MOD].address = company.address;
}

Company* search(HashTable* hash_table, string company_name) {
    int hashValue = hashString(company_name);
    int cnt = 0;
    while (cnt < MOD && hash_table->hashTable[(hashValue + cnt) % MOD].name != "") {
        if (hash_table->hashTable[(hashValue + cnt) % MOD].name == company_name) {
            return &hash_table->hashTable[(hashValue + cnt) % MOD];
        }
        cnt++;
    }
    return NULL;
}

// g++ -std=c++11 *.cpp -o main
// main MST.txt input.txt output.txt

int main(int argc,char* argv[]) {  
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " MST.txt input.txt output.txt" << endl;
        return 1;
    }
    string taxFile = argv[1];
    string inputFile = argv[2];
    string outputFile = argv[3];

    ifstream fin(inputFile);
    ofstream fout(outputFile);
    vector<Company> list_company = readCompanyList(taxFile);
    HashTable* hash_table = createHashTable(list_company);

    string line;
    while(getline(fin, line)) {
        if (line.empty()) continue;
        Company* res = search(hash_table, line);
        if (res != NULL) {
            fout << res->name << "|" << res->profit_tax << "|" << res->address << endl;
        }
    }
    fin.close();
    fout.close();
    return 0;
}
