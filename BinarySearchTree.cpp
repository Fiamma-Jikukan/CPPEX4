#include "BinarySearchTree.h"
#include "Drone.h"

template class BinarySearchTree<Drone>;


template<class T>
BinarySearchTree<T>::BinarySearchTree(): root(nullptr), size(0) {

}

template<class T>
BinarySearchTree<T>::~BinarySearchTree() {
    delete root;
}

template<class T>
void BinarySearchTree<T>::insert(T &data) {
    if (root == nullptr) {
        root = new Node<T>(data);
        size++;
        return;
    }
    Node<T> *curr = root;
    while (curr->left != nullptr || curr->right != nullptr) {
        if (curr->data > data) {
            curr = curr->left;
        }
        if (curr->data < data) {
            curr = curr->right;
        }
        if (curr->data == data) {
            return;
        }
    }
    if (curr->data > data) {
        curr->left = new Node<T>(data);
        curr->left->parent = curr;
    } else {
        curr->right = new Node<T>(data);
        curr->right->parent = curr;
    }
    size++;
}

template<class T>
Node<T> *BinarySearchTree<T>::search(T &data) {
    if (root == nullptr) {
        return nullptr;
    }
    Node<T> curr = root;
    while (curr->left != nullptr && curr->right != nullptr) {
        if (curr->data > data) {
            curr = curr->left;
        }
        if (curr->data < data) {
            curr = curr->right;
        }
        if (curr->data == data) {
            return curr;
        }
    }
    return nullptr;
}

template<class T>
Node<T> *BinarySearchTree<T>::min() {
    if (root == nullptr) {
        return nullptr;
    }
    Node<T> curr = root;
    while (curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

template<class T>
Node<T> *BinarySearchTree<T>::max() {
    if (root == nullptr) {
        return nullptr;
    }
    Node<T> curr = root;
    while (curr->right != nullptr) {
        curr = curr->right;
    }
    return curr;
}

template<class T>
void BinarySearchTree<T>::remove(T &data) {
    if (root == nullptr) {
        return;
    }
    Node<T> curr = root;
    while (curr != nullptr) {
        if (curr->data == data) {
            removeHelper(curr);
            size--;
            return;
        }
        if (data < curr->data) {
            curr = curr->left;
        }
        if (data > curr->data) {
            curr = curr->right;
        }
    }
}

template<class T>
void BinarySearchTree<T>::removeHelper(Node<T> *node) {
    // leaf case
    if (node->left == nullptr && node->right == nullptr) {
        delete node;
    }
    // node has 1 child case
    else if (node->left != nullptr && node->right == nullptr) {
        if (node->parent == nullptr) {
            root = node->left;
            root->parent = nullptr;
            node->left = nullptr;
            delete node;
        } else {
            node->parent->left = node->left;
            node->left->parent = node->parent;
            node->left = nullptr;
            node->parent = nullptr;
            delete node;
        }
    } else if (node->right != nullptr && node->left == nullptr) {
        if (node->parent == nullptr) {
            root = node->right;
            root->parent = nullptr;
            node->right = nullptr;
            delete node;
        } else {
            node->parent->right = node->right;
            node->right->parent = node->parent;
            node->right = nullptr;
            node->parent = nullptr;
            delete node;
        }
    }
    // node has 2 children case
    else if (node->left != nullptr && node->right != nullptr) {
        Node<T> *successor = node->right;
        while (successor->left != nullptr) {
            successor = successor->left;
        }
        node->data = successor->data;
        removeHelper(successor);
    }
}


template<class T>
void BinarySearchTree<T>::clear() const {
    delete root;
}

template<class T>
void BinarySearchTree<T>::print() {
    if (root == nullptr) {
        return;
    }
    root->print();
}

template<class T>
unsigned int BinarySearchTree<T>::GetSize() const {
    return size;
}

template<class T>
Node<T> * BinarySearchTree<T>::GetRoot() const {
    return root;
}
