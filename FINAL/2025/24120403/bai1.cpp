#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<stack>

using namespace std;

int main() {
    int n; cin >> n;
    int sum = n * (n + 1) / 2;
    if(sum % 2 == 1) {
        cout << "NO";
        return 0;
    }
    cout << "YES" << endl;
    int target = sum / 2;
    vector<int> A,B;
    for(int i = n;i >= 1;i--) {
        if(target >= i) {
            target -= i;
            A.push_back(i);
        }
        else {
            B.push_back(i);
        }
    }
    cout << A.size() << endl;
    for(int x : A) {
        cout << x << " ";
    }
    cout << endl;
    cout << B.size() << endl;
    for(int x : B) {
        cout << x << " ";
    }
    return 0;
}