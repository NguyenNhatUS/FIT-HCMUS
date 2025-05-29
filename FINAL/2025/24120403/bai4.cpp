#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<iostream>

using namespace std;

const int MAX = 2 * 1e5 + 1;

vector<bool> visited(MAX,false);
vector<int> res(MAX,0);
vector<vector<int>> tree(MAX);

int dfs(int u) {
    int cnt = 0;
    visited[u] = true;
    for(int v : tree[u]) {
        if(!visited[v]) {
            cnt += 1 + dfs(v);
        }
    }
    res[u] = cnt;
    return cnt;
}

int main() {
    int n; cin >> n;
    for(int i = 2;i <= n;i++) {
        int boss; cin >> boss;
        tree[boss].push_back(i);
    }
    dfs(1);
    for(int i = 1;i <= n;i++) {
        cout << res[i] << " ";
    }
    return 0;
}