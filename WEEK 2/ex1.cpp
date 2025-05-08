//Linear Search
#include<iostream>
#include<math.h>
using namespace std; 

int LinearSearch(int a[],int n,int target) {
    for(int i = 0;i < n;i++) {
        if(a[i] == target) return i;
    }
    return -1;
}

int main() {
    int n; cin >> n;
    int a[n] = {1,5,7,8,5,3,2,1};
    int target = 5;
    cout << LinearSearch(a,n,target) << endl;
    return 0;
}