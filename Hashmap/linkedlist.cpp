#include <iostream>
#include <vector>


template <typename T1, typename T2>
struct Node {
    T1 key;
    std::vector<T2> data;
    Node <T1, T2>*  next;
};


template <typename T1, typename T2>
Node<T1, T2>* addnode(T1 key, T2 data){
    Node <T1, T2> *node = new Node<T1, T2>;
    node->key = key;
    node->data.push_back(data);
    node->next = nullptr;
    return node;
}


