// Is sorted Array
#include<iostream>
#include<math.h>

using namespace std;

bool isSorted(int arr[],int n) {
    if(n == 0 || n == 1) return true; // base case
    if(*arr > *(arr + 1)) return false; // if first element > second element, it's not sorted => return false
    return isSorted(arr + 1,n - 1);  // recursive case
}

int main() {
    int arr[] = {1,2,9,4,5}; // Example of an sorted array
    int n = (sizeof(arr) / sizeof(arr[0]));  // Get array size
    if(isSorted(arr,n)) {
        cout << "The array is sorted " << endl;
    }
    else {
        cout << "The array is NOT sorted " << endl;
    }
    return 0;
}