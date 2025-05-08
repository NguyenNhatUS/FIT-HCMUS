#include<iostream>
#include<math.h>
#include<vector>
using namespace std; 

bool check(vector<int> weights,int days,int weight) {
    int currWeights = 0;
    --days;
    for(int i = 0;i < weights.size();i++) {
        if(currWeights + weights[i] <= weight) {
            currWeights += weights[i];
        }
        else {
            --days;
            currWeights = weights[i];
        }
    }
    return days >= 0;
}

int minWeightToShipWithinDays(vector<int> weights,int days) {
    int maxWeight = 0;
    int res = -1;
    for(int i = 0;i < weights.size();i++) {
       maxWeight += weights[i];
    }
    int left = 1;
    int right = maxWeight;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(check(weights,days,mid)) {
            res = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return res;
}

int main() {
    int days = 5;
    vector<int> weights = {1,2,3,4,5,6,7,8,9,10};
    cout << minWeightToShipWithinDays(weights,days) << endl;
    return 0;
}