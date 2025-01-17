#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <iostream>
using namespace std;

template<class T>
class Node {
private:
    T data;
    Node *left;
    Node *right;
    Node *parent;

public:
    Node(T data, Node *left, Node *right, Node *parent) : data(data), left(left), right(right), parent(parent) {
    }

    explicit Node(T data): data(data), left(nullptr), right(nullptr), parent(nullptr) {
    }

    ~Node() {
        delete left;
        delete right;
    }

    T getData() {
        return data;
    }

    void setData(T data) {
        this->data = data;
    }

    Node *getLeft() {
        return left;
    }

    void setLeft(Node *node) {
        left = node;
    }

    Node *getRight() {
        return right;
    }

    void setRight(Node *node) {
        right = node;
    }

    Node *getParent() {
        return parent;
    }

    void setParent(Node *node) {
        parent = node;
    }

    void printNode(Node *node) {
        if (node == nullptr) {
            return;
        }
        printNode(node->left);
        cout << node->getData() << " ";
        printNode(node->right);
    }
};

template<class T>
class BinarySearchTree {
private:
    Node<T> *root;
    unsigned int size;

public:
    explicit BinarySearchTree(T &rootData);

    ~BinarySearchTree();

    void insert(T &data);

    Node<T> * search(T &data);

    Node<T> *min();

    Node<T> *max();

    void remove(T &data);

    void removeHelper(Node<T> *node);

    void clear() const;

    void print();

    unsigned int GetSize() const;
};


#endif //BINARYSEARCHTREE_H
