#include<iostream>
#include<fstream>
#include<queue>
#include<string>
#include<math.h>
#include<sstream>
#include<algorithm>

using namespace std;

struct Player {
    string name,date, nation, club;
    int height, weight;
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
    getline(ss,token,',');
    newNode->p.name = token;
    getline(ss,token,',');
    newNode->p.date = token;
    getline(ss,token,',');
    newNode->p.height = stoi(token);
    getline(ss,token,',');
    newNode->p.weight = stoi(token);
    getline(ss,token,',');
    newNode->p.nation = token;
    getline(ss,token,',');
    newNode->p.club = token;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root,Node* p) {
    if(root == NULL) return p;
    if(root->p.name > p->p.name) {
        root->left = insert(root->left,p);
    }
    else if(root->p.name < p->p.name) {
        root->right = insert(root->right,p);
    }
    return root;
}

Node* createPlayerTree(string filename) {
    Node* root = NULL;
    ifstream fin(filename);
    string line;
    while(getline(fin,line)) {
        if(line.empty()) continue;
        Node* node = makeNode(line);
        if(node->p.height >= 175) {
            root = insert(root,node);
        }
    }
    fin.close();
    return root;
}

void processDate(string date,int& d,int& m,int& y) {
    stringstream ss(date);
    string token;
    getline(ss,token,'-');
    d = stoi(token);
    getline(ss,token,'-');
    m = stoi(token);
    getline(ss,token,'-');
    y = stoi(token);
}

void PlayerTreeTraversal(Node* pRoot) {
    if(pRoot == NULL) return;
    queue<Node*> q;
    q.push(pRoot);
    int level = 0;
    while(!q.empty()) {
        int len = q.size();
        for(int i = 0;i < len;i++) {
            Node* node = q.front(); q.pop();
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
            cout << level << "-";
            cout << node->p.name << "-";
            int d,m,y;
            processDate(node->p.date,d,m,y);
            cout << y << endl;
        }
        level++;
    }
}

Node* getSucc(Node* node) {
    Node* curr = node;
    while(curr && curr->left) {
        curr = curr->left;
    }
    return curr;
}

Node* deleteNode(Node* root,Node* p) {
    if(root == NULL) return NULL;
    if(root->p.name > p->p.name) {
        root->left = deleteNode(root->left,p);
    }
    else if(root->p.name < p->p.name) {
        root->right = deleteNode(root->right,p);
    }
    else {
        if(root->left == NULL) {
            Node* tmp = root->right;
            delete root;
            return tmp;
        }
        if(!root->right) {
            Node* tmp = root->left;
            delete root;
            return tmp;
        }
        Node* succ = getSucc(root->right);
        root->p = succ->p;
        root->right = deleteNode(root,succ);
    }
    return root;
}

Node* remove(Node* root,char C) {
    if (!root) return NULL;
    root->left = remove(root->left, C);
    root->right = remove(root->right, C);
    if (root->p.name[0] == C) {
        Node* temp = root;
        if (!root->left) {
            root = root->right;
        }
        else if (!root->right) {
            root = root->left;
        }
        else {
            Node* succ = getSucc(root->right);
            root->p = succ->p;
            root->right = deleteNode(root->right, succ);
            return root;
        }
        delete temp;
    }
    return root;
}

void removePlayers(Node* &pRoot, vector <char> C) {
    if(pRoot == NULL) return;
    for(char c : C) {
        pRoot = remove(pRoot,c);
    }
}

bool isGreater(int d,int m,int y,int d1,int m1,int y1) {
    if(y < y1) return true;
    if(y == y1 && m < m1) return true;
    if(y == y1 && m == m1 && d < d1) return true;
    return false;
}

void findPlayers(Node* pRoot) {
    if(pRoot == NULL) return;
    queue<Node*> q;
    q.push(pRoot);
    vector<string> name;
    while(!q.empty()) {
        Node* node = q.front();
        q.pop();
        if(node->left && node->right) {
            int d,m,y;
            processDate(node->p.date,d,m,y);
            int d1,m1,y1;
            processDate(node->right->p.date,d1,m1,y1);
            int d2,m2,y2;
            processDate(node->left->p.date,d2,m2,y2);
            if(isGreater(d,m,y,d1,m1,y1) && isGreater(d,m,y,d2,m2,y2)) {
                name.push_back(node->p.name);
            }
        }
        if(node->left) q.push(node->left);
        if(node->right) q.push(node->right);
    }
    sort(name.begin(),name.end());
    for(string s : name) {
        cout << s << endl;
    }
}

int main() {
    Node* root = createPlayerTree("Players.csv");
    PlayerTreeTraversal(root);
    vector<char> removeChars = {'L', 'K'};
    removePlayers(root, removeChars);
    PlayerTreeTraversal(root);
    findPlayers(root);
    return 0;
}