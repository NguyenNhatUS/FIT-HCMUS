#include<iostream>
#include<sstream>
#include<fstream>
#include<string.h>


using namespace std;

struct Node {
    int key;
    Node* next;
};

struct Stack {
    Node* top;
    Node* tail;
};

Node* makeNode(int key) {
    Node* newNode = new Node;
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

Stack* initializeStack() {
    Stack* st = new Stack;
    st->top = st->tail = nullptr;
    return st;
}

void push(Stack &s, int key) {
    if(s.top == NULL) {
        s.top = s.tail = makeNode(key);
        return;
    }
    Node* newNode = makeNode(key);
    s.tail->next = newNode;
    s.tail = newNode;
}

void disPlay(ofstream& os,Stack *s) {
    if(s->top == NULL) {
        os << "EMPTY" << endl;
        return;
    }
    Node* tmp = s->top;
    while(tmp != NULL) {
        os << tmp->key << " ";
        tmp = tmp->next;
    }
    os << endl;
}

int pop(Stack &s) {
    if(s.top == NULL) {
        cout << "EMPTY" << endl;
        return -1;
    }
    int val = s.tail->key;
    if(s.top == s.tail) {
        s.top = s.tail = NULL;
    }
    else {
        Node* tmp = s.top;
        while(tmp != NULL && tmp->next != s.tail) {
            tmp = tmp->next;
        }
        s.tail = tmp;
        s.tail->next = NULL;
        tmp = tmp->next;
        delete tmp;
    }
    return val;
}

int size(Stack s) {
    Node* tmp = s.top;
    int cnt = 0;
    while(tmp != NULL) {
        cnt++;
        tmp = tmp->next;
    }
    return cnt;
}

bool isEmpty(Stack s) {
    return s.top == NULL;
}

int main() {
    ifstream fin("input.txt");
    string line;
    ofstream fout("output.txt");
    Stack* st;
    while(getline(fin,line)) {
        stringstream ss(line);
        string token;
        ss >> token;
        if(token == "init") {
            st = initializeStack();
            fout << "EMPTY" << endl;
        }
        else if(token == "push") {
            ss >> token;
            int key = stoi(token);
            push(*st,key);
            disPlay(fout,st);
        }
        // if token == "pop"
        else {
            pop(*st);
            disPlay(fout,st);
        }
    }
    fin.close();
    fout.close();
    return 0;
}