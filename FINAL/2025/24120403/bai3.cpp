#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<iostream>

using namespace std;

int n,m;
int cnt = 0;

bool check(int i,int j,vector<vector<char>>& grid) {
    return i >= 0 && i < n && j >= 0 && j < m && grid[i][j] == '.';
}

int idx[4] = {-1,0,1,0};
int idy[4] = {0,1,0,-1};

void loang(int i,int j,vector<vector<char>>& grid) {
    grid[i][j] = '#';
    for(int k = 0;k < 4;k++) {
        int i1 = i + idx[k];
        int j1 = j + idy[k];
        if(check(i1,j1,grid)) {
            loang(i1,j1,grid);
        } 
    }
}

int main() {
    cin >> n >> m;
    vector<vector<char>> grid(n,vector<char>(m));
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < m;j++) {
            cin >> grid[i][j];
        }
    }

    for(int i = 0;i < n;i++) {
        for(int j = 0;j < m;j++) {
            if(grid[i][j] == '.') {
                cnt++;
                loang(i,j,grid);
            }
        }
    }
    cout << cnt << endl;
    return 0;
}