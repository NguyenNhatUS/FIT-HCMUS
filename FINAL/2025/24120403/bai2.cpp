#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<iostream>
#include<set>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    Node(int data) {
        key = data;
        left = right = NULL;
        height = 1;
    }
};

int height(Node* root) {
    if(root == NULL) return 0;
    return root->height;
}

int getBalance(Node* root) {
    if(root == NULL) return 0;
    return height(root->left) - height(root->right);
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T = y->left;
    y->left = x;
    x->right = T;
    x->height = 1 + max(height(x->left),height(x->right));
    y->height = 1 + max(height(y->left),height(y->right));
    return y;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T = x->right;
    x->right = y;
    y->left = T;
    x->height = 1 + max(height(x->left),height(x->right));
    y->height = 1 + max(height(y->left),height(y->right));
    return x;
}

Node* insert(Node* root,int key) {
    if(root == NULL) return new Node(key);
    if(root->key > key) {
        root->left = insert(root->left,key);
    }
    else {
        root->right = insert(root->right,key);
    }
    root->height = 1 + max(height(root->left),height(root->right));
    int balance = getBalance(root);
    if(balance > 1 && key < root->left->key) {
        return rightRotate(root);
    }
    if(balance < -1 && key > root->right->key) {
        return leftRotate(root);
    }
    if(balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Node* getSucc(Node* node) {
    Node* curr = node;
    while(curr->left) {
        curr = curr->left;
    }
    return curr;
}

int findKey(Node* root, int target) {
    int res = -1;
    while (root != NULL) {
        if (root->key <= target) {
            res = root->key;
            root = root->right;
        } 
        else {
            root = root->left;
        }
    }
    return res;
}

Node* deleteNode(Node* root,int key) {
    if(root == NULL) return NULL;
    if(root->key > key) {
        root->left = deleteNode(root->left,key);
    }
    else if(root->key < key) {
        root->right = deleteNode(root->right,key);
    }
    else {
        if(root->left == NULL) {
            Node* tmp = root->right;
            delete root;
            return tmp;
        }
        if(root->right == NULL) {
            Node* tmp = root->left;
            delete root;
            return tmp;
        }
        Node* succ = getSucc(root->right);
        root->key = succ->key;
        root->right = deleteNode(root->right,succ->key);
    }

    int balance = getBalance(root);
    if(balance > 1 && getBalance(root->left) > 0) {
        return rightRotate(root);
    }
    if(balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }
    if(balance > 1 && getBalance(root->left) <= 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void inorder(Node* root) {
    if(root != NULL) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

int main() {
    int n,m; cin >> n >> m;
    vector<int> h(n), t(m);
    Node* root = NULL;
    for(int i = 0;i < n;i++) {
        cin >> h[i];
        root = insert(root,h[i]);
    }
    for(int i = 0;i < m;i++) {
        cin >> t[i];
    }
    for(int i = 0;i < m;i++) {
        int val = findKey(root,t[i]);
        cout << val << endl;
        if(val != -1) root = deleteNode(root,val);
    }
    return 0;
}