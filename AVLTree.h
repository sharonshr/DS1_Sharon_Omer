
#ifndef AVLTREE_H
#define AVLTREE_H

template<typename Key, typename Value>
class AVLTree {
private:
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;
        int height;
        Node(const Key& k, const Value& v)
            : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    void destroyTree(Node* node);
    Node* insertRec(Node* node, const Key&, const Value&);
    Node* removeRec(Node* node, const Key&);
    Node* rebalance(Node* node);
    Node* rotateLeft(Node*);
    Node* rotateRight(Node*);
    void updateHeight(Node*);
    int getHeight(Node*) const;
    int getBalance(Node*) const;
    void destroyValuesRec(Node* node);

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree();

    void insert(const Key&, const Value&);
    void remove(const Key&);
    Value* find(const Key&) const;
    bool contains(const Key&) const;
    bool isEmpty() const;
    void destroyValues();
    int maxHeight(int a, int b);

};


template<typename Key, typename Value>
void AVLTree<Key,Value>::destroyTree(Node* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

template<typename Key, typename Value>
AVLTree<Key,Value>::AVLTree::~AVLTree() {
    destroyTree(this->root);
}

template<typename Key, typename Value>
int AVLTree<Key,Value>::getHeight(Node* node) const {
    if (node == nullptr) {
        return  0;
    }
    return node->height;
}

template<typename Key, typename Value>
int AVLTree<Key,Value>::maxHeight(int a, int b)  {
    return (a > b) ? a : b;
}

template<typename Key, typename Value>
void AVLTree<Key,Value>::updateHeight(Node* node) {
    node->height = 1 + maxHeight(getHeight(node->left),getHeight(node->right));
}

template<typename Key, typename Value>
int AVLTree<Key,Value>::getBalance(Node* node) const {
    if (node == nullptr) {
        return 0;
    }
    int balance = getHeight(node->left) - getHeight(node->right);
    return balance;
}

template<typename Key, typename Value>
typename AVLTree<Key,Value>::Node*
AVLTree<Key,Value>::rebalance(Node* node){

    int balance = getBalance(node);
    // LL
    if (balance == 2 && getBalance(node->left) >= 0)
        return rotateRight(node);
    // LR
    if (balance == 2 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // RR
    if (balance == -2 && getBalance(node->right) <= 0)
        return rotateLeft(node);
    // RL
    if (balance == -2 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

//this function returns the updated root of the tree (or subtree)
template<typename Key, typename Value>
typename AVLTree<Key,Value>::Node*
AVLTree<Key,Value>::rotateRight(Node* a) {
    Node* b = a->left;
    Node* b_right = b->right;

    b->right = a;
    a->left = b_right;

    updateHeight(a);
    updateHeight(b);

    return b;
}

//this function returns the updated root of the tree (or subtree)
template<typename Key, typename Value>
typename AVLTree<Key,Value>::Node*
AVLTree<Key,Value>::rotateLeft(Node* b) {
    Node* a = b->right;
    Node* a_left = a->left;

    a->left = b;
    b->right = a_left;

    updateHeight(b);
    updateHeight(a);

    return a;
}

template<typename Key, typename Value>
void AVLTree<Key,Value>::insert(const Key& key, const Value& value){
    root = insertRec(root, key, value);
}


//this function returns the updated root of the tree (or subtree)
template <typename Key, typename Value>
typename AVLTree<Key, Value>::Node*
AVLTree<Key,Value>::insertRec(Node* node,const Key& key,const Value& value){
    if (!node) {
        return new Node(key,value);
    }
    if (key < node->key) {
        node->left = insertRec(node->left, key, value);
    } else if (key > node->key) {
        node->right = insertRec(node->right, key, value);
    } else {
        node->value = value;
        return node;
    }

    updateHeight(node);

    return rebalance(node);

}
template<typename Key, typename Value>
typename AVLTree<Key,Value>::Node*
AVLTree<Key,Value>::removeRec(Node* node, const Key& key) {
    if (!node) {
        return nullptr;
    }

    if (key < node->key) {
        node->left = removeRec(node->left, key);
    }
    else if (key > node->key) {
        node->right = removeRec(node->right, key);
    }
    else {
        if (!node->left || !node->right) {
            Node* child = node->left ? node->left : node->right;
            delete node;
            return child;
        } else {
            Node* successor = node->right;
            while (successor->left)
                successor = successor->left;
            node->key = successor->key;
            node->value = successor->value;
            node->right = removeRec(node->right, successor->key);
        }
    }
    updateHeight(node);
    return rebalance(node);
}

template<typename Key, typename Value>
void AVLTree<Key,Value>::remove(const Key& key) {
    root = removeRec(root, key);
}

template<typename Key, typename Value>
Value* AVLTree<Key,Value>::find(const Key& key) const {
    Node* cur = root;
    while (cur) {
        if (key < cur->key) cur = cur->left;
        else if (key > cur->key) cur = cur->right;
        else return &(cur->value);
    }
    return nullptr;
}

template<typename Key, typename Value>
bool AVLTree<Key,Value>::contains(const Key& key) const {
    return (find(key) != nullptr);
}

template<typename Key, typename Value>
bool AVLTree<Key,Value>::isEmpty() const {
    return (root == nullptr);
}

template<typename Key, typename Value>
void AVLTree<Key,Value>::destroyValues() {
    destroyValuesRec(root);
}

template<typename Key, typename Value>
void AVLTree<Key,Value>::destroyValuesRec(Node* node) {
    if (!node) return;
    destroyValuesRec(node->left);
    destroyValuesRec(node->right);
    delete node->value;
}

#endif //AVLTREE_H
