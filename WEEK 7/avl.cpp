#include<queue>
#include<iostream>
#include<math.h>
#include<vector>

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

Node* createNode(int data) {
    return new Node(data);
}

int getHeight(Node* root) {
    if(root == NULL) return 0;
    return root->height;
}

int getBalance(Node* root) {
    if(root == NULL) return 0;
    return getHeight(root->left) - getHeight(root->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T = x->right;
    x->right = y;
    y->left = T;
    x->height = 1 + max(getHeight(x->left),getHeight(x->right));
    y->height = 1 + max(getHeight(y->left),getHeight(y->right));
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T = y->left;
    y->left = x;
    x->right = T;
    x->height = 1 + max(getHeight(x->left),getHeight(x->right));
    y->height = 1 + max(getHeight(y->left),getHeight(y->right));
    return y;
}

Node* insert(Node*& root,int x) {
    if(root == NULL) return createNode(x);
    if(root->key > x) {
        root->left = insert(root->left,x);
    }
    else if(root->key < x) {
        root->right = insert(root->right,x);
    }
    else {
        return root;
    }
    root->height = 1 + max(getHeight(root->left),getHeight(root->right));
    int balance = getBalance(root);
    // Right Right Case
    if(balance < -1 && x > root->right->key) {
        return leftRotate(root);
    }
    // Left Left Case
    if(balance > 1 && x < root->left->key) {
        return rightRotate(root);
    }
    // Right Left Case
    if(balance < -1 && x > root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    // Left Right Case
    if(balance > 1 && x > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    return root;
}

void Insert(Node*& root,int x) {
    root = insert(root,x);
}

Node* getSucc(Node* node) {
    Node* curr = node;
    while(curr && curr->left) {
        curr = curr->left;
    }
    return curr;
}

Node* deleteNode(Node*& root,int x) {
    if(root == NULL) return NULL;
    if(root->key > x) {
        root->left = deleteNode(root->left,x);
    }
    else if(root->key < x) {
        root->right = deleteNode(root->right,x);
    }
    else {
        if(root->left == NULL || root->right == NULL) {
            Node* tmp = (root->left) ? root->left : root->right;
            if(tmp == NULL) {
                tmp = root;
                root = NULL;
            }
            else {
                *root = *tmp;
            }
            delete tmp;
        }
        else {
            Node* succ = getSucc(root->right);
            root->key = succ->key;
            root->right = deleteNode(root->right,succ->key);
        }
    }
    if(root == NULL) return NULL;
    root->height = 1 + max(getHeight(root->left),getHeight(root->right));
    int balance = getBalance(root);
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    return root;
}

void Remove(Node*& root,int x) {
    root = deleteNode(root,x);   
}

bool checkIfAVL(Node* root) {
    if(root == NULL) return true;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    if(abs(leftHeight - rightHeight) > 1) return false;
    return checkIfAVL(root->left) && checkIfAVL(root->right);
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

void inorder(Node* root) {
    if(root != NULL) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

bool isAVL(Node* root) {
    return isBST(root) && checkIfAVL(root);
}