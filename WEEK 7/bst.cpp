#include<iostream>
#include<queue>
#include<vector>

using namespace std;
struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int value) {
        key = value;
        left = right = nullptr;
    }
};

Node* Search(Node* root,int x) {
    if(root == NULL) return root;
    if(root->key > x) {
        root->left = Search(root->left,x);
    }
    else if(root->key < x) {
        root->right = Search(root->right,x);
    }
    else {
        return root;
    }
}

void Insert(Node*& root,int x) {
    if(root == NULL) {
        root = new Node(x);
        return;
    }
    Node* curr = root;
    Node* parent = NULL;
    while(curr != NULL) {
        parent = curr;
        if(curr->key > x) {
            curr = curr->left;
        }
        else if(curr->key < x) {
            curr = curr->right;
        }
        else {
            return;
        }
    }
    if(parent->key > x) {
        parent->left = new Node(x);
    }
    else {
        parent->right = new Node(x);
    }
}

Node* getSucc(Node* root) {
    Node* curr = root;
    while(curr && curr->left) {
        curr = curr->left;
    }
    return curr;
}

Node* deleteNode(Node* root,int x) {
    if(root == NULL) return NULL;
    if(root->key > x) {
        root->left = deleteNode(root->left,x);
    }
    else if(root->key < x) {
        root->right = deleteNode(root->right,x);
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
    return root;
}

void Remove(Node*& root,int x) {
    root = deleteNode(root,x);
}

Node* createTree(int a[],int n) {
    Node* root = NULL;
    for(int i = 0;i < n;i++) {
        Insert(root,a[i]);
    }
    return root;
}

void removeTree(Node* root) {
    if(root == NULL) return;
    removeTree(root->left);
    removeTree(root->right);
    Remove(root,root->key);
}

int Height(Node* root) {
    if(root == NULL) return -1;
    return 1 + max(Height(root->left),Height(root->right));
}

int countNode(Node* root) {
    if(root == NULL) return 0;
    return 1 + countNode(root->left) + countNode(root->right);
}

int countLess(Node* root,int x) {
    if(root == NULL) return 0;
    int cnt = (root->key < x) ? 1 : 0;
    return cnt + countLess(root->left,x) + countLess(root->right,x);
}

int countGreater(Node* root,int x) {
    if(root == NULL) return 0;
    int cnt = (root->key > x) ? 1 : 0;
    return cnt + countGreater(root->left,x) + countGreater(root->right,x);
}

void inOrder(Node* root,vector<int>& res) {
    if(root != NULL) {
        inOrder(root->left,res);
        res.push_back(root->key);
        inOrder(root->right,res);
    }
}

bool isBST(Node* root) {
    vector<int> res;
    inOrder(root,res);
    for(int i = 0;i < res.size() - 1;i++) {
        if(res[i] >= res[i + 1]) return false;
    }
    return true;
}

bool isFullbst(Node* root) {
    if(root == NULL) return true;
    if(root->left == NULL && root->right == NULL) return true;
    if(root->left && root->right) {
        return isFullbst(root->left) && isFullbst(root->right);
    }
    return false;
}

bool isFullBST(Node* root) {
    return isBST(root) && isFullbst(root);
}

void inOrder(Node* root) {
    if(root != NULL) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}


