#include<iostream>
#include<math.h>
using namespace std; 

int minLength(int a[],int n,int target) {
    int left = 0;
    int right;
    int sum = 0;
    int minLen = INT_MAX;
    for(right = 0;right < n;right++) {
        sum += a[right];
        while(sum >= target) {
            if(minLen > (right - left + 1)) {
                minLen = right - left + 1;
            }
            sum -= a[left++];
        }
    }
    return minLen;
}

int main() {
    int a[] = {1,2,3,4,5,6,7,8,9,10};
    int n = sizeof(a) / sizeof(a[0]);
    cout << minLength(a,n,20) << endl;
    return 0;
}