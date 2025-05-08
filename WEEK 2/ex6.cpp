#include<iostream>
#include<math.h>
using namespace std; 

bool check(int a[],int n,int target) {
    int left = 0,right = n - 1;
    while(left < right) {
        int sum = a[left] + a[right];
        if(sum == target) return true;
        else if(sum < target) {
            left++;
        }
        else {
            right--;
        }
    }
    return false;
}


int main() {
    int a[] = {1,4,5,7,8,14,19};
    int n = sizeof(a) / sizeof(a[0]);
    if(check(a,n,15)) cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}