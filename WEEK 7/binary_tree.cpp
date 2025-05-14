#include<iostream>
#include<queue>
#include<vector>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->key = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Pre-order
void preOrder(Node* root,vector<int>& res) {
    if(root != NULL) {
        res.push_back(root->key);
        preOrder(root->left,res);
        preOrder(root->right,res);
    }
}

vector<int> NLR(Node* root) {
    vector<int> res;
    preOrder(root,res);
    return res;
}

// In-order
void inOrder(Node* root,vector<int>& res) {
    if(root != NULL) {
        inOrder(root->left,res);
        res.push_back(root->key);
        inOrder(root->right,res);
    }
}

vector<int> LNR(Node* root) {
    vector<int> res;
    inOrder(root,res);
    return res;
}

void postOrder(Node* root,vector<int>& res) {
    if(root != NULL) {
        postOrder(root->left,res);
        postOrder(root->right,res);
        res.push_back(root->key);
    }
}

// Post-order
vector<int> LRN(Node* root) {
    vector<int> res;
    postOrder(root,res);
    return res;
}

vector<vector<int>> LevelOrder(Node* root) {
    vector<vector<int>> res;
    if(root == NULL) return {};
    queue<Node*> q;
    q.push(root);
    while(!q.empty()) {
        int len = q.size();
        vector<int> tmp;
        for(int i = 0;i < len;i++) {
            Node* node = q.front(); q.pop();
            tmp.push_back(node->key);
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        res.push_back(tmp);
    }
    return res;
}

int countNode(Node* root) {
    if(root == NULL) return 0;
    return 1 + countNode(root->left) + countNode(root->right);
}

int sumNode(Node* root) {
    if(root == NULL) return 0;
    return root->key + sumNode(root->left) + sumNode(root->right);
}

int getHeight(Node* root) {
    if(root == NULL) return -1;
    return 1 + max(getHeight(root->left),getHeight(root->right));
}

int heightNode(Node* root,int value) {
    if(root == NULL) return -1;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()) {
        Node* node = q.front(); q.pop();
        if(node->key == value) {
            return getHeight(node);
        }
        if(node->left) q.push(node->left);
        if(node->right) q.push(node->right);
    }
    return -1;
}

int Level(Node* root,Node* p) {
    if(root == NULL) return -1;
    queue<Node*> q;
    q.push(root);
    int currLevel = 0;
    while(!q.empty()) {
        int len = q.size();
        for(int i = 0;i < len;i++) {
            Node* node = q.front(); q.pop();
            if(node == p) return currLevel;
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        currLevel++;
    }
    return -1;
}

int countLeaf(Node* root) {
    int cnt = 0;
    if(root == NULL) return 0;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()) {
        Node* node = q.front(); q.pop();
        if(node->left == NULL && node->right == NULL) {
            cnt++;
            continue;
        }
        if(node->left) q.push(node->left);
        if(node->right) q.push(node->right);
    }
    return cnt;
}
