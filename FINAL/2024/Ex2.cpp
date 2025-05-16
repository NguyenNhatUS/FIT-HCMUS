#include<iostream>
#include<math.h>
#include<sstream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

const int M = 1e9 + 7;

struct Player {
    string name, date, nation, club;
    long long height, weight;
};

Player* make(string s) {
    Player* p = new Player;
    stringstream ss(s);
    string token;
    getline(ss,token,',');
    p->name = token;
    getline(ss,token,',');
    p->date = token;
    getline(ss,token,',');
    p->height = stoi(token);
    getline(ss,token,',');
    p->weight = stoi(token);
    getline(ss,token,',');
    p->nation = token;
    getline(ss,token,',');
    p->club = token;
    return p;
}

long long sumDigit(long long n) {
    long long res = 0;
    while(n) {
        res += n % 10;
        n /= 10;
    }
    return res;
}

long long power(long long a,long long b) {
    a %= M;
    long long res = 1;
    while(b) {
        if(b % 2 == 1) {
            res = (res * a) % M;
        }
        a = (a * a) % M;
        b /= 2;
    }
    return res;
}

long long sumChar(string s) {
    long long res = 0;
    for(int i = 0;i < s.size();i++) {
        res += 1ll * (int(s[i]) - 65);
    }
    return res;
}

void processDate(string date,int &d,int &m,int &y) {
    stringstream ss(date);
    string token;
    getline(ss,token,'-');
    d = stoi(token);
    getline(ss,token,'-');
    m = stoi(token);
    getline(ss,token,'-');
    y = stoi(token);
}

long long Hashing(Player p) {
    long long res = 0;
    long long sumchar = sumChar(p.name);
    int d,m,y;
    processDate(p.date,d,m,y);
    long long sumdigit = sumDigit(y);
    res = power(d,sumchar) % M;
    res = (res * power(m,d)) % M;
    res = (res * power(sumdigit,m)) % M;
    res = (res * power(sumchar,sumdigit)) % M;
    return res;
}

void insert(Player*& hashTable,Player p) {
    long long hashVal = Hashing(p) % 2500;
    int cnt = 0;
    while(hashTable[(hashVal + cnt) % 2500].name != "") {
        cnt++;
    }
    hashTable[(hashVal + cnt) % 2500] = p;
}

Player* createHash(string filename, int &size) {
    Player* hashTable = new Player[size];
    for(int i = 0;i < size;i++) {
        hashTable[i].name = "";
        hashTable[i].date = "";
        hashTable[i].nation = "";
        hashTable[i].club = "";
        hashTable[i].height = hashTable[i].weight = -1;
    }
    ifstream fin(filename);
    string line;
    while(getline(fin,line)) {
        Player* p = make(line);
        insert(hashTable,*p);
    }
    fin.close();
    return hashTable;
}

void printHashtable(Player*& hashTable, int size) {
    for(int i = 0;i < size;i++) {
        cout << i << ": ";
        cout << hashTable[i].name << " ";
        cout << hashTable[i].date << " ";
        cout << hashTable[i].height << " ";
        cout << hashTable[i].weight << " ";
        cout << hashTable[i].nation << " ";
        cout << hashTable[i].club << endl;
    }
}

bool cmp(Player a,Player b) {
    return a.name == b.name && a.date == b.date && a.height == b.height
    && a.weight == b.weight && a.nation == b.nation && a.club == b.club;
}

Player search(Player* hashTable, Player P) {
    long long hashVal = Hashing(P);
    int cnt = 0;
    while(hashTable[(hashVal + cnt) % 2500].name != "") {
        if(cmp(hashTable[(cnt + hashVal) % 2500],P)) {
            return P;
        }
        cnt++;
    }
    return hashTable[(cnt + hashVal) % 2500];
}

void Remove(Player* hashTable, Player P) {
    long long hashVal = Hashing(P);
    int cnt = 0;
    while(hashTable[(hashVal + cnt) % 2500].name != "") {
        if(cmp(hashTable[(cnt + hashVal) % 2500],P)) {
            hashTable[(cnt + hashVal) % 2500].name = "";
            hashTable[(cnt + hashVal) % 2500].date = "";
            hashTable[(cnt + hashVal) % 2500].weight = -1;
            hashTable[(cnt + hashVal) % 2500].height = -1;
            hashTable[(cnt + hashVal) % 2500].nation = "";
            hashTable[(cnt + hashVal) % 2500].club = "";
            return;
        }
        cnt++;
    }
}

int main() {
    int size = 2500;
    Player* hashTable = createHash("Players.csv", size);
    Player target;
    target.name = "Cristiano Ronaldo";
    target.date = "05-02-1985";
    target.height = 187;
    target.weight = 83;
    target.nation = "Portugal";
    target.club = "Al Nassr";
    Player found = search(hashTable, target);
    if (found.name == "NOT FOUND") {
        cout << "Player not found.\n";
    } 
    else {
        cout << "Found player: " << found.name << endl;
    } 
    printHashtable(hashTable, size);
    delete[] hashTable;
    return 0;
}