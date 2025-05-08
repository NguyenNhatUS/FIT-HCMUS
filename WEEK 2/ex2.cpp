#include<iostream>
#include<math.h>
using namespace std; 

int linearSearchWithSentinel(int a[],int n,int target) {
    int last = a[n - 1];
    int i = 0;
    a[n - 1] = target;
    while(a[i] != target) {
        i++;
    }
    a[n - 1] = last;
    if(i < n - 1 || a[n - 1] == target) return i;
    return -1;
}

int main() {
    int a[] = {1,5,7,8,5,3,2,1};
    int n = sizeof(a) / sizeof(a[0]);
    int target = 5;
    cout << linearSearchWithSentinel(a,n,target);
    return 0;
}