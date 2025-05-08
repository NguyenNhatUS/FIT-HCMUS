#include<iostream>
#include<math.h>
using namespace std; 

void merge(int a[],int left,int mid,int right) {
    int n = right - left + 1;
    int* tmp = new int[n];
    int idx = 0;
    int i = left;
    int j = mid + 1;
    while(i <= mid && j <= right) {
        if(a[i] <= a[j]) {
            tmp[idx++] = a[i++];
        }
        else {
            tmp[idx++] = a[j++];
        }
    }
    while(i <= mid) {
        tmp[idx++] = a[i++];
    }
    while(j <= right) {
        tmp[idx++] = a[j++];
    }
    for(int i = 0;i < n;i++) {
        a[i + left] = tmp[i];
    }
    delete[] tmp;
}

void mergeSort(int a[],int left,int right) {
    if(left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(a,left,mid);
    mergeSort(a,mid + 1,right);
    merge(a,left,mid,right);
}

void findAlltriples(int a[],int n,int target) {
    mergeSort(a,0,n - 1);
    for(int i = 0;i < n;i++) {
        if(a[i] > 0) return;
        if(i > 0 && a[i] == a[i - 1]) continue;
        int j = i + 1;
        int k = n - 1;
        while(j < k) {
            int sum = a[i] + a[j] + a[k];
            if(sum < target) {
                j++;
            }
            else if(sum > target) {
                k--;
            }
            else {
                cout << a[i] << " " << a[j] << " " << a[k] << endl;
                j++;
                k--;
                while(j < k && a[j] == a[j - 1]) j++;
            }
        }
    }
}

int main() {
    int a[] = {-1,0,1,2,-1,-4};
    int n = sizeof(a) / sizeof(a[0]);
    int target = 0;
    findAlltriples(a,n,target);
    return 0;
}