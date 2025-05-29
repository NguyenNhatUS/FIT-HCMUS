#include<iostream>
#include<vector>
#include<math.h>
#include<fstream>
#include<sstream>
#include<string>
#include<queue>
#include<cstring>
#include<algorithm>
#include<stack>
#include <limits>

using namespace std;

// 1,
vector<vector<int>> convertMatrixToList(const string& filename) {
    ifstream fin(filename);
    string line;
    getline(fin,line);
    int n = stoi(line);
    vector<vector<int>> res(n);
    int i = 0,j = 0;
    while(getline(fin,line)) {
        stringstream ss(line);
        string token;
        while(ss >> token) {
            int num = stoi(token);
            if(num) {
                res[i].push_back(j);
            }
            j++;
        }
        i++;
        j = 0;
    }
    fin.close();
    return res;
}

vector<vector<int>> convertMatrixToList(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> adjList(n,vector<int> (n,0));
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < n;j++) {
            if(adjMatrix[i][j]) {
                adjList[i].push_back(j);
            }
        }
    }
    return adjList;
}

// 2,
vector<vector<int>> convertListToMatrix(const string& filename) {
    ifstream fin(filename);
    string line;
    getline(fin,line);
    int n = stoi(line);
    vector<vector<int>> res(n,vector<int> (n,0));
    int i = 0;
    while(getline(fin,line)) {
        stringstream ss(line);
        string token;
        ss >> token;
        while(ss >> token) {
            int j = stoi(token);
            res[i][j] = 1;
        }
        i++;
    }
    fin.close();
    return res;
}

// 3,
bool isDirected(const vector<vector<int>> & adjMatrix) {
    int n = adjMatrix.size();
    for(int i = 0;i < n;i++) {
        for(int j = i + 1;j < n;j++) {
            if(adjMatrix[i][j] && !adjMatrix[j][i]) return true;
        }
    }
    return false;
}

int countVertices(const vector<vector<int>>& adjMatrix) {
    return adjMatrix.size();
}

int countEdges(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size(), cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cnt += adjMatrix[i][j];
        }
    } 
    return isDirected(adjMatrix) ? cnt : cnt / 2;
}

// List of isolated vertices.
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
    vector<int> res;
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i) {
        bool isolated = true;
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] || adjMatrix[j][i]) {
                isolated = false;
                break;
            }
        }
        if (isolated) res.push_back(i);
    }
    return res;
}

// Undirected Graph.
bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
    int n = countVertices(adjMatrix);
    int m = countEdges(adjMatrix);
    return m == n * (n - 1) / 2;
}

// Undirected Graph
bool isBipartite(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> color(n,-1);
    for(int i = 0;i < n;i++) {
        if(adjMatrix[i][i]) return false;
        if(color[i] != -1) continue;
        color[i] = 0;
        queue<int> q;
        q.push(i);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(int v = 0;v < n;v++) {
                if(adjMatrix[u][v]) {
                    if(color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    }
                    else if(color[u] == color[v]) return false;
                }
            }
        }
    }
    return true;
}

// // Undirected Graph
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> color(n,-1);
    for(int i = 0;i < n;i++) {
        if(adjMatrix[i][i]) return false;
        if(color[i] != -1) continue;
        color[i] = 0;
        queue<int> q;
        q.push(i);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(int v = 0;v < n;v++) {
                if(adjMatrix[u][v]) {
                    if(color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    }
                    else if(color[u] == color[v]) return false;
                }
            }
        }
    }
    int cnt1 = 0;
    int cnt0 = 0;
    for(int x : color) {
        if(x == 0) cnt0++;
        else cnt1++;
    }
    int edges = countEdges(adjMatrix);
    return edges == cnt1 * cnt0;
}

// 4,
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> undirectedMatrix(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(adjMatrix[i][j]) {
                undirectedMatrix[i][j] = 1;
                undirectedMatrix[j][i] = 1;
            }
        }
    }
    return undirectedMatrix;
}

// 5,
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> res(n);
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < n;j++) {
            if(i != j && !adjMatrix[i][j]) {
                res[i].push_back(j);
            }
        }
    }
    return res;
}

// 6,
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> graph = adjMatrix;
    stack<int> st;
    vector<int> cycle;
    vector<int> degree(n,0);

    bool directed = isDirected(adjMatrix);

    if (!directed) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                degree[i] += graph[i][j];
        }
        for(int i = 0;i < n;i++) {
            if(degree[i] % 2 == 1) {
                cout << i << endl;
                cout << "Không có chu trình Euler (đỉnh bậc lẻ trong đồ thị vô hướng)" << endl;
                return {};
            }
        }
    } 
    else {
        for (int i = 0; i < n; ++i) {
            int outDeg = 0, inDeg = 0;
            for (int j = 0; j < n; ++j) {
                outDeg += graph[i][j];
                inDeg += graph[j][i];
            }
            if (inDeg != outDeg) {
                cout << "Không có chu trình Euler (inDeg != outDeg trong đồ thị có hướng)\n";
                return {};
            }
        }
    }

    // Hierholzer's Algorithm
    st.push(0);

    while (!st.empty()) {
        int u = st.top();
        bool hasEdge = false;

        for (int v = 0; v < n; ++v) {
            if (graph[u][v] > 0) {
                st.push(v);
                graph[u][v]--;
                if (!directed) graph[v][u]--;  // nếu vô hướng thì xóa cạnh ngược
                hasEdge = true;
                break;
            }
        }
        if (!hasEdge) {
            cycle.push_back(u);
            st.pop();
        }
    }
    return cycle;
}

//7,
void dfsBuildTree(vector<vector<int>>& adjList,int u,vector<bool>& visited,vector<vector<int>>& tree) {
    visited[u] = true;
    for(int v : adjList[u]) {
        if(!visited[v]) {
            tree[u].push_back(v);
            tree[v].push_back(u);
            dfsBuildTree(adjList,v,visited,tree);
        }
    }
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<vector<int>> adjList = convertMatrixToList(adjMatrix);
    vector<vector<int>> tree(n);
    vector<bool> visited(n,false);
    dfsBuildTree(adjList,start,visited,tree);
    return tree;
}

void bfsBuildTree(vector<vector<int>>& adjList,int start,vector<bool>& visited,vector<vector<int>>& tree) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int v : adjList[u]) {
            if(!visited[v]) {
                tree[u].push_back(v);
                tree[v].push_back(u);
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<vector<int>> adjList = convertMatrixToList(adjMatrix);
    vector<bool> visited(n,false);
    vector<vector<int>> tree(n);
    bfsBuildTree(adjList,start,visited,tree);
    return tree;
}

// 8,
void dfs(vector<vector<int>>& adj,int u,vector<bool> visited,vector<int>& cnt,int count) {
    visited[u] = true;
    cnt[u] = count;
    for(int v : adj[u]) {
        if(!visited[v]) {
            dfs(adj,v,visited,cnt,count);
        }
    }
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
    vector<vector<int>> adj = convertMatrixToList(adjMatrix);
    int n = adjMatrix.size();

    vector<bool> visited(n, false);
    vector<int> cnt(n, 0);
    int count = 0;
    for(int i = 0;i < n;i++) {
        if(!visited[i]) {
            count++;
            dfs(adj,i,visited,cnt,count);
        }
    }
    return cnt[u] == cnt[v];
}

vector<vector<pair<int,int>>> convertWeightedMatrixToList(vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<pair<int,int>>> adjList(n);
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < n;j++) {
            if(adjMatrix[i][j]) {
                adjList[i].push_back({j,adjMatrix[i][j]});
            }
        }
    }
    return adjList;
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> dist(n,INT_MAX);
    vector<int> parent(n,-1);
    vector<bool> visited(n,false);
    dist[start] = 0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0,start});
    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if(visited[u]) continue;
        visited[u] = true;
        for(int v = 0;v < n;v++) {
            if(adjMatrix[u][v]) {
                int w = adjMatrix[u][v];
                if(dist[v] > w + dist[u]) {
                    dist[v] = w + dist[u];
                    parent[v] = u;
                    pq.push({dist[v],v});
                }
            }
        }
    }
    vector<int> path;
    if(dist[end] == INT_MAX) return {};
    while(end != -1) {
        path.push_back(end);
        end = parent[end];
    }
    reverse(path.begin(),path.end());
    return path;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);

    dist[start] = 0;

    for (int k = 0; k < n - 1; ++k) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (adjMatrix[u][v] != 0 && dist[u] != INT_MAX) {
                    if (dist[u] + adjMatrix[u][v] < dist[v]) {
                        dist[v] = dist[u] + adjMatrix[u][v];
                        parent[v] = u;
                    }
                }
            }
        }
    }

    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] != 0 && dist[u] != INT_MAX) {
                if (dist[u] + adjMatrix[u][v] < dist[v]) {
                    return {};
                }
            }
        }
    }

    vector<int> path;
    if (dist[end] == INT_MAX) return path; 

    while(end != -1) {
        path.push_back(end);
        end = parent[end];
    }
    reverse(path.begin(), path.end());
    return path;
}