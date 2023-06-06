#include <iostream>
using namespace std;

class ThreadedNode {
public:
    int value;
    ThreadedNode* left;
    ThreadedNode* right;
    bool isThreaded;

    ThreadedNode(int val) {
        value = val;
        left = nullptr;
        right = nullptr;
        isThreaded = false;
    }
};

class ThreadedBinarySearchTree {
private:
    ThreadedNode* root;

    ThreadedNode* findSuccessor(ThreadedNode* node) {
        if (node->isThreaded)
            return node->right;
        node = node->right;
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

public:
    ThreadedBinarySearchTree() {
        root = nullptr;
    }

void insert(int val) {
    ThreadedNode* newNode = new ThreadedNode(val);
    if (root == nullptr) {
        root = newNode;
        return;
    }

    ThreadedNode* curr = root;
    while (true) {
        if (val < curr->value) {
            if (curr->left == nullptr) {
                curr->left = newNode;
                newNode->right = curr;
                newNode->isThreaded = true;
                return;
            }
            curr = curr->left;
        }
        else {
            if (curr->isThreaded || curr->right == nullptr) {
                newNode->right = curr->right;
                newNode->isThreaded = true;
                curr->right = newNode;
                curr->isThreaded = false;
                return;
            }
            curr = curr->right;
            break;
        }
    }
}



    void inorder() {
        ThreadedNode* curr = root;
        while (curr->left != nullptr)
            curr = curr->left;

        while (curr != nullptr) {
            cout << curr->value << " ";

            if (curr->isThreaded)
                curr = curr->right;
            else
                curr = findSuccessor(curr);
        }
        cout << endl;
    }

    void preorder() {
        if (root == nullptr)
            return;

        ThreadedNode* curr = root;
        while (curr != nullptr) {
            cout << curr->value << " ";

            if (curr->left != nullptr)
                curr = curr->left;
            else if (curr->right != nullptr && !curr->isThreaded)
                curr = curr->right;
            else {
                while (curr != nullptr && curr->right != nullptr && curr->isThreaded)
                    curr = curr->right;
                if (curr != nullptr)
                    curr = curr->right;
            }
        }
        cout << endl;
    }

    ThreadedNode* findNode(int val) {
        ThreadedNode* curr = root;
        while (curr != nullptr) {
            if (curr->value == val)
                return curr;

            if (val < curr->value)
                curr = curr->left;
            else if (curr->isThreaded)
                curr = nullptr;
            else
                curr = curr->right;
        }
        return nullptr;
    }

    void deleteNode(int val) {
        ThreadedNode* target = findNode(val);
        if (target == nullptr)
            return;

        if (target->isThreaded) {
            if (target->left != nullptr)
                target->left->right = target->right;
            if (target->right != nullptr && !target->right->isThreaded)
                target->right->left = target->left;
        }
        else {
            ThreadedNode* successor = findSuccessor(target);
            if (successor->left != nullptr)
                successor->left->right = successor->right;
            if (successor->right != nullptr && !successor->isThreaded)
                successor->right->left = successor->left;
            successor->left = target->left;
            successor->right = target->right;
        }

        if (target == root)
            root = findSuccessor(target);
        delete target;
    }
};

int main() {
    ThreadedBinarySearchTree tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    cout << "In-order traversal: ";
    tree.inorder();

    cout << "Pre-order traversal: ";
    tree.preorder();

    tree.deleteNode(3);
    cout << "After deleting node with value 3:" << endl;

    cout << "In-order traversal: ";
    tree.inorder();

    cout << "Pre-order traversal: ";
    tree.preorder();

    return 0;
}
