#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include<vector>
#include<math.h>

using namespace std;

struct Player {
    string name;
    string date;
    int height;
    int weight;
    string nation;
    string club;
};

struct Node {
    Player p;
    Node* left;
    Node* right;
};

Node* makeNode(string s) {
    Node* newNode = new Node;
    stringstream ss(s);
    string token;
    getline(ss, token, ','); newNode->p.name = token;
    getline(ss, token, ','); newNode->p.date = token;
    getline(ss, token, ','); newNode->p.height = stoi(token);
    getline(ss, token, ','); newNode->p.weight = stoi(token);
    getline(ss, token, ','); newNode->p.nation = token;
    getline(ss, token, ','); newNode->p.club = token;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void processDate(string date, int& d, int& m, int& y) {
    stringstream ss(date);
    string token;
    getline(ss, token, '-'); d = stoi(token);
    getline(ss, token, '-'); m = stoi(token);
    getline(ss, token, '-'); y = stoi(token);
}

int cmp(Node* a, Node* b) {
    if (a->p.name < b->p.name) return -1;
    if (a->p.name > b->p.name) return 1;
    return 0;
}

Node* insert(Node* root, Node* p) {
    if (!root) return p;
    if (cmp(p, root) < 0)
        root->left = insert(root->left, p);
    else if (cmp(p, root) > 0)
        root->right = insert(root->right, p);
    return root;
}

Node* createPlayerTree(string filename) {
    ifstream fin(filename);
    string line;
    Node* root = NULL;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        Node* p = makeNode(line);
        int d, m, y;
        processDate(p->p.date, d, m, y);
        if (1 <= d && d <= 15) {
            root = insert(root, p);
        }
    }
    fin.close();
    return root;
}

void PlayerTreeTraversal(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    int currLevel = 0;
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            Node* node = q.front(); q.pop();
            int d, m, y;
            processDate(node->p.date, d, m, y);
            cout << currLevel << " - " << node->p.name << " - " << y << endl;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        currLevel++;
    }
}

Node* getSucc(Node* node) {
    Node* curr = node;
    while (curr && curr->left) curr = curr->left;
    return curr;
}

Node* deleteNode(Node* root, Node* p) {
    if (!root) return NULL;
    if (p->p.name < root->p.name)
        root->left = deleteNode(root->left, p);
    else if (p->p.name > root->p.name)
        root->right = deleteNode(root->right, p);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* succ = getSucc(root->right);
        root->p = succ->p;
        root->right = deleteNode(root->right, succ);
    }
    return root;
}

Node* removePlayers(Node* root, char C) {
    if (!root) return NULL;
    root->left = removePlayers(root->left, C);
    root->right = removePlayers(root->right, C);
    if (!root->p.name.empty() && root->p.name[0] == C) {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* succ = getSucc(root->right);
        root->p = succ->p;
        root->right = deleteNode(root->right, succ);
    }
    return root;
}

void findPlayers(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front(); q.pop();
        if (node->left && node->right) {
            int total = node->p.height + node->left->p.height + node->right->p.height;
            if (total > 550) {
                cout << node->p.name << endl;
            }
        }
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}

int main() {
    Node* root = createPlayerTree("Players.csv");
    cout << "=== Level Order Traversal ===\n";
    PlayerTreeTraversal(root);
    cout << "\n=== Cầu thủ có tổng chiều cao > 550 và có 2 con ===\n";
    findPlayers(root);
    cout << "\n=== Xóa cầu thủ có tên bắt đầu bằng ký tự 'C' ===\n";
    root = removePlayers(root, 'L');
    cout << "\n=== Cây sau khi xóa ===\n";
    PlayerTreeTraversal(root);
    return 0;
}
