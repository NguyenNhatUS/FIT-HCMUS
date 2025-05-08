#include<iostream>
#include<sstream>
#include<fstream>
#include<string.h>


using namespace std;

struct Node {
    int key;
    Node* next;
};

struct Queue {
    Node* head;
    Node* tail;
};

Node* makeNode(int key) {
    Node* newNode = new Node;
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

Queue* initializeQueue() {
    Queue* q = new Queue;
    q->head = q->tail = NULL;
    return q;
}

void disPLay(ostream &os, Queue* q) {
    if(q->head == NULL) {
        os << "EMPTY" << endl;
        return;
    }
    Node* tmp = q->head;
    while(tmp != NULL) {
        os << tmp->key << " ";
        tmp = tmp->next;
    }
    os << endl;
}

void enqueue(Queue &q, int key) {
    Node* newNode = makeNode(key);
    if(q.head == NULL) {
        q.head = q.tail = newNode;
        return;
    }
    q.tail->next = newNode;
    q.tail = newNode;
}

int dequeue(Queue &q) {
    if(q.head == NULL) {
        return -1;
    }
    int val = q.head->key;
    if(q.head == q.tail) {
        q.head = q.tail = NULL;
    }
    else {
        Node* tmp = q.head;
        q.head = tmp->next;
        delete tmp;
    }
    return val;
}

int size(Queue q) {
    Node* tmp = q.head;
    int cnt = 0;
    while(tmp != NULL) {
        cnt++;
        tmp = tmp->next;
    }
    return cnt;
}

bool isEmpty(Queue q) {
    return q.head == NULL;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    string line;
    Queue* q;
    while(getline(fin,line)) {
        stringstream ss(line);
        string token;
        ss >> token;
        if(token == "init") {
            q = initializeQueue();
            fout << "EMPTY" << endl;
        }
        else if(token == "enqueue") {
            ss >> token;
            int key = stoi(token);
            enqueue(*q,key);
            disPLay(fout,q);
        }
        // else if token == "dequeue"
        else {
            dequeue(*q);
            disPLay(fout,q);
        }
    }
    fin.close();
    fout.close();
    return 0;
}