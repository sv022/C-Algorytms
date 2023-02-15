#include <iostream>
#include <set>

struct Node {
    int data;
    Node* next;
};

Node* addnode(int data){
    Node* node = new Node;
    node->data = data;
    node->next = nullptr;
    return node;
}

Node* linkedlist(int n){
    if (n < 1) throw std::exception();
    Node* head = addnode(rand() % 100);
    if (n == 1) return head;
    Node* tail = addnode(rand() % 100);
    head->next = tail;
    for (int i = 0; i < n - 2; i++){
        Node* node = addnode(rand() % 100);
        tail->next = node;
        tail = node;
    }
    return head;
}

Node* linkedlist(){
    return nullptr;
}

void printl(Node* head){
    if (head == nullptr) return;
    Node* p = head;
    while (p->next){
        std::cout << p->data << " ~ ";
        p = p->next;
    }
    std::cout << p->data << '\n';
}

int suml(Node* head){
    Node* p = head;
    int s = 0;
    while (p){
        s += p->data;
        p = p->next;
    }
    return s;
}

void push_back(Node* &head, const int value){
    Node* node = addnode(value);
    if (head == nullptr) {head = node; return;}
    if (head->next == nullptr) {head->next = node; return;}
    Node* p = head->next;
    while (p->next) p = p->next;
    p->next = node;
}

void push_front(Node* &head, const int value){
    Node* node = addnode(value);
    node->next = head;
    head = node;
}

void insertl(Node* &head, const int value, const int n){
    Node* node = addnode(value);
    Node* p = head->next;
    for (int i = 0; i < n - 2; i++) p = p->next;
    node->next = p->next;
    p->next = node;
}

int len(Node* head){
    if (head == nullptr) return 0;
    Node* p = head->next;
    int k = 1;
    while (p){
        k++;
        p = p->next;
    }
    return k;
}

int pop(Node* &head, const int n){
    if (head == nullptr) throw std::exception();
    if (n == 0) {int t = head->data; head = head->next; return t;}
    if (n == 1) {int t = head->next->data; head->next = head->next->next; return t;}
    Node* p = head->next;
    for (int i = 0; i < n - 2; i++) p = p->next;
    Node *t = p->next;
    p->next = p->next->next;
    return t->data;
}

bool isempty(Node* head){
    return head == nullptr;
}

bool eq(Node* l1, Node* l2){
    if (l1 == nullptr and l2 == nullptr) return true;
    if (l1 == nullptr or l2 == nullptr) return false;
    Node* p1 = l1;
    Node* p2 = l2;
    while (p1 and p2) {
        if (p1->data != p2->data) return false;
        p1 = p1->next;
        p2 = p2->next;
    }
    if (p1 == p2) return true;
    return false;
}

bool issubset(Node* sub, Node* sup){
    if (sub == nullptr and sup == nullptr) return true;
    if (sup == nullptr) return false;
    if (sub == nullptr) return true;
    std::set <int> s1;
    std::set <int> s2;
    Node* p1 = sub;
    Node* p2 = sup;
    while (p1){
        s1.insert(p1->data);
        p1 = p1->next;
    }
    while (p2) {
        s2.insert(p2->data);
        p2 = p2->next;
    }
    return std::includes(s1.begin(), s1.end(), s2.begin(), s2.end());
}

bool isunique(Node* head){
    if (head == nullptr) return true;
    if (head->next == nullptr) return true;
    Node* p = head;
    std::set <int> s;
    while (p){
        s.insert(p->data);
        p = p->next;
    }
    return s.size() == len(head);
}

void exchangeend(Node* &head){
    int n = len(head) - 1;
    push_front(head, pop(head, n));
}

void exchangefront(Node* &head){
    if (head == nullptr) return;
    push_back(head, head->data);
    pop(head, 0);
}

void extend(Node* &head, Node* item){
    if (item == nullptr) return;
    if (head == nullptr) {head = item; return;}
    Node* p = item;
    while (p){
        push_back(head, p->data);
        p = p->next;
    }
}

void reverse(Node* &head){
    if (head == nullptr) return;
    Node* res = linkedlist();
    Node* p = head;
    while (p){
        push_front(res, p->data);
        p = p->next;
    }
    delete head;
    head = res;
}

void strip(Node* &head){
    if (head == nullptr) return;
    std::set <int> s;
    Node* p = head;
    while (p){
        s.insert(p->data);
        p = p->next;
    }
    Node* res = linkedlist();
    for (auto x : s) push_back(res, x);
    delete head;
    head = res;
}