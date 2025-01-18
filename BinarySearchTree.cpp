#include "BinarySearchTree.h"
#include "Drone.h"

template class BinarySearchTree<Drone>;


template<class T>
BinarySearchTree<T>::BinarySearchTree(): root(nullptr), size(0) {

}

template<class T>
BinarySearchTree<T>::~BinarySearchTree() {
    // Clean up all nodes in the tree
    clear();
}

//
// Post-order traversal to delete entire subtree
//
template<class T>
void BinarySearchTree<T>::ClearTree(Node<T>* node) {
    if (node == nullptr) return;

    // Recursively delete left and right children
    ClearTree(node->getLeft());
    ClearTree(node->getRight());

    // Now it is safe to delete this node
    delete node;
}

//
// Clear the entire BST
//
template<class T>
void BinarySearchTree<T>::clear() {
    // Delete everything under root
    ClearTree(root);
    root = nullptr;
    size = 0;
}

template<class T>
void BinarySearchTree<T>::insert(T &data) {
    if (root == nullptr) {
        root = new Node<T>(data);
        size++;
        return;
    }
    Node<T> *curr = root;
    while (curr->getLeft() != nullptr || curr->getRight() != nullptr) {
        if (curr->getData() > data) {
            curr = curr->getLeft();
        }
        if (curr->getData() < data) {
            curr = curr->getRight();
        }
        if (curr->getData() == data) {
            return;
        }
    }
    if (curr->getData() > data) {
        curr->setLeft(new Node<T>(data));
        curr->getLeft()->setParent(curr);
    } else {
        curr->setRight(new Node<T>(data))  ;
        curr->getRight()->setParent(curr);
    }
    size++;
}

template<class T>
Node<T> *BinarySearchTree<T>::search(T &data) {
    if (root == nullptr) {
        return nullptr;
    }
    Node<T> *curr = root;
    while (curr->getLeft() != nullptr && curr->getRight() != nullptr) {
        if (curr->getData() > data) {
            curr = curr->getLeft();
        }
        if (curr->getData() < data) {
            curr = curr->getRight();
        }
        if (curr->getData() == data) {
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
    Node<T> *curr = root;
    while (curr->getLeft() != nullptr) {
        curr = curr->getLeft();
    }
    return curr;
}

template<class T>
Node<T> *BinarySearchTree<T>::max() {
    if (root == nullptr) {
        return nullptr;
    }
    Node<T> *curr = root;
    while (curr->getRight() != nullptr) {
        curr = curr->getRight();
    }
    return curr;
}

template<class T>
void BinarySearchTree<T>::remove(T &data) {
    if (root == nullptr) {
        return;
    }
    Node<T> *curr = root;
    while (curr != nullptr) {
        if (curr->getData() == data) {
            removeHelper(curr);
            size--;
            return;
        }
        if (data < curr->getData()) {
            curr = curr->getLeft();
        }
        if (data > curr->getData()) {
            curr = curr->getRight();
        }
    }
}

template<class T>
void BinarySearchTree<T>::removeHelper(Node<T> *node) {
    // leaf case
    if (node->getLeft() == nullptr && node->getRight() == nullptr) {
        delete node;
    }
    // node has 1 child case
    else if (node->getLeft() != nullptr && node->getRight() == nullptr) {
        if (node->getParent() == nullptr) {
            root = node->getLeft();
            root->setParent(nullptr) ;
            node->setLeft(nullptr);
            delete node;
        } else {
            node->getParent()->setLeft(node->getLeft());
            node->getLeft()->setParent(node->getParent());
            node->setLeft(nullptr);
            node->setParent(nullptr) ;
            delete node;
        }
    } else if (node->getRight() != nullptr && node->getLeft() == nullptr) {
        if (node->getParent() == nullptr) {
            root = node->getRight();
            root->setParent(nullptr);
            node->setRight(nullptr);
            delete node;
        } else {
            node->getParent()->setRight(node->getRight());
            node->getRight()->setParent(node->getParent());
            node->setRight(nullptr);
            node->setParent(nullptr);
            delete node;
        }
    }
    // node has 2 children case
    else if (node->getLeft() != nullptr && node->getRight() != nullptr) {
        Node<T> *successor = node->getRight();
        while (successor->getLeft() != nullptr) {
            successor = successor->getLeft();
        }
        node->getData() = successor->getData();
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
    root->printNode(root);
}

template<class T>
unsigned int BinarySearchTree<T>::GetSize() const {
    return size;
}

template<class T>
Node<T> * BinarySearchTree<T>::GetRoot() const {
    return root;
}
