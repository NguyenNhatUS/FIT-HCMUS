//Generate Binary String
#include<iostream>
#include<string.h>
using namespace std;

//Backtracking funtion to generate all binary strings of length n
void generateBinaryStrings(int n, string &str) {
    if(str.size() == n) {   // Base case
        cout << str << endl;
        return;
    }
    char c[2] = {'0','1'};
    for(int j = 0;j < 2;j++) {
        str += c[j];
        generateBinaryStrings(n,str);  // recursive case
        str.pop_back();  // backtrack
    }
}

int main() {
    int n; cin >> n;  //Value of n
    string str = "";
    cout << "All Binary String of length " << n << " are: " << endl;
    generateBinaryStrings(n,str);
    return 0;
}