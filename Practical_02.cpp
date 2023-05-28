#include <iostream>
#include <stack>
using namespace std;

class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
private:
    TreeNode* root;

    void destroyTree(TreeNode* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    ~BinaryTree() {
        destroyTree(root);
    }

    void insert(int val) {
        TreeNode* newNode = new TreeNode(val);

        if (root == nullptr) {
            root = newNode;
            return;
        }

        TreeNode* curr = root;
        while (true) {
            if (val < curr->value) {
                if (curr->left == nullptr) {
                    curr->left = newNode;
                    return;
                }
                curr = curr->left;
            } else {
                if (curr->right == nullptr) {
                    curr->right = newNode;
                    return;
                }
                curr = curr->right;
            }
        }
    }

    void inorderRecursive(TreeNode* node) {
        if (node == nullptr)
            return;

        inorderRecursive(node->left);
        cout << node->value << " ";
        inorderRecursive(node->right);
    }

    void inorder() {
        inorderRecursive(root);
        cout << endl;
    }

    void preorderRecursive(TreeNode* node) {
        if (node == nullptr)
            return;

        cout << node->value << " ";
        preorderRecursive(node->left);
        preorderRecursive(node->right);
    }

    void preorder() {
        preorderRecursive(root);
        cout << endl;
    }

    void postorderRecursive(TreeNode* node) {
        if (node == nullptr)
            return;

        postorderRecursive(node->left);
        postorderRecursive(node->right);
        cout << node->value << " ";
    }

    void postorder() {
        postorderRecursive(root);
        cout << endl;
    }

    void swapTree(TreeNode* node) {
        if (node == nullptr)
            return;

        TreeNode* temp = node->left;
        node->left = node->right;
        node->right = temp;

        swapTree(node->left);
        swapTree(node->right);
    }

    void swapTreeNodes() {
        swapTree(root);
    }

    int getHeight(TreeNode* node) {
        if (node == nullptr)
            return 0;

        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);

        return max(leftHeight, rightHeight) + 1;
    }

    int getHeight() {
        return getHeight(root);
    }

    TreeNode* copyTreeRecursive(TreeNode* node) {
        if (node == nullptr)
            return nullptr;

        TreeNode* newNode = new TreeNode(node->value);
        newNode->left = copyTreeRecursive(node->left);
        newNode->right = copyTreeRecursive(node->right);

        return newNode;
    }

    BinaryTree copyTree() {
        BinaryTree copiedTree;
        copiedTree.root = copyTreeRecursive(root);
        return copiedTree;
    }

    int countLeavesRecursive(TreeNode* node) {
        if (node == nullptr)
            return 0;

        if (node->left == nullptr && node->right == nullptr)
            return 1;

        return countLeavesRecursive(node->left) + countLeavesRecursive(node->right);
    }

    int countLeaves() {
        return countLeavesRecursive(root);
    }

    int countInternalNodesRecursive(TreeNode* node) {
        if (node == nullptr || (node->left == nullptr && node->right == nullptr))
            return 0;

        return 1 + countInternalNodesRecursive(node->left) + countInternalNodesRecursive(node->right);
    }

    int countInternalNodes() {
        return countInternalNodesRecursive(root);
    }

    void eraseTree() {
        destroyTree(root);
        root = nullptr;
    }
};

int main() {
    BinaryTree tree;
    int values[] = { 5, 3, 7, 1, 4, 6, 8 };

    for (int value : values)
        tree.insert(value);

    cout << "Inorder traversal: ";
    tree.inorder();

    cout << "Preorder traversal: ";
    tree.preorder();

    cout << "Postorder traversal: ";
    tree.postorder();

    tree.swapTreeNodes();
    cout << "After swapping left and right pointers: ";
    tree.inorder();

    cout << "Height of the tree: " << tree.getHeight() << endl;

    BinaryTree copiedTree = tree.copyTree();
    cout << "Inorder traversal of copied tree: ";
    copiedTree.inorder();

    cout << "Number of leaves: " << tree.countLeaves() << endl;
    cout << "Number of internal nodes: " << tree.countInternalNodes() << endl;

    tree.eraseTree();
    cout << "Tree erased." << endl;

    return 0;
}
