#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<sstream>

using namespace std;

struct Node {
    int* a;
    int n;
    Node* left;
    Node* right;
    int height;
};

int height(Node* root) {
    if(root == NULL) return 0;
    return root->height;
}

int getBalance(Node* root) {
    if(root == NULL) return 0;
    return height(root->left) - height(root->right);
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

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T = y->left;
    y->left = x;
    x->right = T;
    x->height = 1 + max(height(x->left),height(x->right));
    y->height = 1 + max(height(y->left),height(y->right));
    return y;
}

Node* makeNode(int* a,int n) {
    Node* newNode = new Node;
    newNode->n = n;
    newNode-> a = new int[n];
    for(int i = 0;i < n;i++) {
        newNode->a[i] = a[i];
    }
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

int sum(Node* A) {
    if(A == NULL) return 0;
    int res = 0;
    for(int i = 0;i < A->n;i++) {
        res += A->a[i];
    }
    return res;
}

bool isGreater(Node* A,Node* B) {
    return ((sum(A) > sum(B)) || (sum(A) == sum(B) && A->n > B->n));
}

bool isEqual(Node* A,Node* B) {
    if(sum(A) != sum(B)) return false;
    if(A->n != B->n) return false;
    for(int i = 0;i < A->n;i++) {
        if(A->a[i] != B->a[i]) return false;
    }
    return true;
}

Node* insert(Node* root,Node* p) {
    if(root == NULL) return p;
    if(isEqual(root,p)) return root;
    if(isGreater(root,p)) {
        root->left = insert(root->left,p);
    }
    else {
        root->right = insert(root->right,p);
    }
    if(root == NULL) return NULL;
    root->height = 1 + max(height(root->left),height(root->right));
    int balance = getBalance(root);
    if(balance > 1 && isGreater(root,p)) {
        return rightRotate(root);
    }
    if(balance < -1 && !isGreater(root,p)) {
        return leftRotate(root);
    }
    if(balance > 1 && !isGreater(root,p)) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && isGreater(root,p)) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

vector<int> processString(string s) {
    vector<int> res;
    stringstream ss(s);
    string token;
    ss >> token;
    while(ss >> token) {
        res.push_back(stoi(token));
    }
    return res;
}

Node* createTree(string filename) {
    Node* root = NULL;
    ifstream fin(filename);
    string line;
    while(getline(fin,line)) {
        if(line.empty()) continue;
        vector<int> res = processString(line);
        int n = res.size();
        int* a = new int[n];
        for(int i = 0;i < n;i++) {
            a[i] = res[i];
        }
        Node* p = makeNode(a,n);
        root = insert(root,p);
        delete[] a;
    }
    fin.close();
    return root;
}

void levelOrder(Node* root) {
    if(root == NULL) return;
    int currLevel = 0;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()) {
        int len = q.size();
        for(int i = 0;i < len;i++) {
            Node* node = q.front();
            q.pop();
            cout << "Level ";
            cout << currLevel << ": ";
            for(int i = 0;i < node->n;i++) {
                cout << node->a[i] << " ";
            }
            cout << endl;
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        currLevel++;
    }
}

Node* getSucc(Node* node) {
    Node* curr = node;
    while(curr && curr->left) {
        curr = curr->left;
    }
    return curr;
}

Node* deleteNode(Node*& root,Node* p) {
    if(root == NULL) return nullptr;
    if(isGreater(root,p)) {
        root->left = deleteNode(root->left,p);
    }
    else if(!isGreater(root,p)) {
        root->right = deleteNode(root->right,p);
    }
    else if(isEqual(root,p)) {
        if(root->left == NULL || root->right == NULL) {
            Node* tmp = root->left ? root->left : root->right;
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
            delete[] root->a;
            root->n = succ->n;
            root->a = new int[root->n];
            for(int i = 0;i < root->n;i++) {
                root->a[i] = succ->a[i];
            }   
            root->right = deleteNode(root->right,succ);
        }
    }
    if(root == NULL) return NULL;
    root->height = 1 + max(height(root->left),height(root->right));
    int balance = getBalance(root);
    if(balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }
    if(balance < -1 && getBalance(root->right) < 0) {
        return leftRotate(root);
    }
    if(balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && getBalance(root->right) >= 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void remove(Node*& pRoot,int *a,int n) {
    if(pRoot == NULL) return;
    Node* p = makeNode(a,n);
    pRoot = deleteNode(pRoot,p);
}

int main() {
    Node* root = createTree("inputAVL.txt");
    cout << "Level Order Traversal of AVL Tree: " << endl;
    levelOrder(root);
    int arr[] = {1, 2, 3}; 
    remove(root, arr, 3);
    cout << "Tree after removal:" << endl;
    levelOrder(root);
    return 0;
}
