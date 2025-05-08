#include<iostream>
#include<math.h>
using namespace std; 

int MinValueInRotatedArray(int a[],int n) {
    int left = 0;
    int right = n - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(a[mid] > a[right]) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return a[left];
}

int main() {
    int a[] = {6,7,1,2,3,4,5};
    int n = (sizeof(a) / sizeof(a[0]));
    cout << MinValueInRotatedArray(a,n) << endl;
    return 0;
}