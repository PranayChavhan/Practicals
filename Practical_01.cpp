#include <iostream>

class BinarySearchTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
    };

    Node* root;

    Node* insertNode(Node* root, int value) {
        if (root == NULL) {
            Node* newNode = new Node;
            newNode->data = value;
            newNode->left = NULL;
            newNode->right = NULL;
            return newNode;
        }
        if (value < root->data) {
            root->left = insertNode(root->left, value);
        }
        else {
            root->right = insertNode(root->right, value);
        }
        return root;
    }

//     Node* insertNode(Node* root, int value) {
//     Node* current = root;
//     Node* parent = NULL;

//     while (current != NULL) {
//         parent = current;

//         if (value < current->data) {
//             current = current->left;
//         }
//         else {
//             current = current->right;
//         }
//     }

//     Node* newNode = new Node;
//     newNode->data = value;
//     newNode->left = NULL;
//     newNode->right = NULL;

//     if (parent == NULL) {
//         root = newNode;
//     }
//     else if (value < parent->data) {
//         parent->left = newNode;
//     }
//     else {
//         parent->right = newNode;
//     }

//     return root;
// }


    int findMaxDepth(Node* root) {
        if (root == NULL) {
            return 0;
        }
        int leftDepth = findMaxDepth(root->left);
        int rightDepth = findMaxDepth(root->right);
        return std::max(leftDepth, rightDepth) + 1;
    }

    int findMinValue(Node* root) {
        if (root == NULL) {
            return 0;
        }
        if (root->left == NULL) {
            return root->data;
        }
        return findMinValue(root->left);
    }

    int findMaxValue(Node* root) {
        if (root == NULL) {
            return 0;
        }
        if (root->right == NULL) {
            return root->data;
        }
        return findMaxValue(root->right);
    }

    void swapLeftRight(Node* root) {
        if (root == NULL) {
            return;
        }
        swapLeftRight(root->left);
        swapLeftRight(root->right);
        Node* temp = root->left;
        root->left = root->right;
        root->right = temp;
    }

    bool searchElement(Node* root, int value) {
        if (root == NULL) {
            return false;
        }
        if (root->data == value) {
            return true;
        }
        if (value < root->data) {
            return searchElement(root->left, value);
        }
        else {
            return searchElement(root->right, value);
        }
    }

    Node* deleteNode(Node* root, int value) {
        if (root == NULL) {
            return NULL;
        }
        if (value < root->data) {
            root->left = deleteNode(root->left, value);
        }
        else if (value > root->data) {
            root->right = deleteNode(root->right, value);
        }
        else {
            if (root->left == NULL && root->right == NULL) {
                // Case 1: leaf node
                delete root;
                root = NULL;
            }
            else if (root->left == NULL) {
                // Case 2: node with one child (right child)
                Node* temp = root;
                root = root->right;
                delete temp;
            }
            else if (root->right == NULL) {
                // Case 2: node with one child (left child)
                Node* temp = root;
                root = root->left;
                delete temp;
            }
            else {
                // Case 3: node with two children
                Node* temp = findMinNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }
        return root;
    }

    Node* findMinNode(Node* root) {
        while (root->left != NULL) {
            root = root->left;
        }
        return root;
    }



public:
    BinarySearchTree() {
        root = NULL;
    }

    void insert(int value) {
        root = insertNode(root, value);
    }

    int getMaxDepth() {
        return findMaxDepth(root);
    }

    int getMinValue() {
        return findMinValue(root);
    }

    int getMaxValue() {
        return findMaxValue(root);
    }

    void swapLeftRight() {
        swapLeftRight(root);
    }

    bool search(int value) {
        return searchElement(root, value);
    }

    void remove(int value) {
        deleteNode(root, value);
    }
};

int main() {
    BinarySearchTree tree;
    int choice;
    do {
        std::cout << "\nBinary Search Tree Operations" << std::endl;
        std::cout << "------------------------------" << std::endl;
        std::cout << "1. Insert a node" << std::endl;
        std::cout << "2. Find maximum depth" << std::endl;
        std::cout << "3. Find minimum and maximum values" << std::endl;
        std::cout << "4. Swap left and right pointers" << std::endl;
        std::cout << "5. Search for an element" << std::endl;
        std::cout << "6. Delete for an element" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cout << "Enter your choice"<<std::endl;
                std::cin >> choice;
        switch (choice) {
        case 1: {
            int value;
            std::cout << "Enter the value to insert: ";
            std::cin >> value;
            tree.insert(value);
            break;
        }
        case 2: {
            int maxDepth = tree.getMaxDepth();
            std::cout << "The maximum depth of the tree is " << maxDepth << std::endl;
            break;
        }
        case 3: {
            int minValue = tree.getMinValue();
            int maxValue = tree.getMaxValue();
            std::cout << "The minimum value in the tree is " << minValue << std::endl;
            std::cout << "The maximum value in the tree is " << maxValue << std::endl;
            break;
        }
        case 4: {
            tree.swapLeftRight();
            std::cout << "Left and right pointers have been swapped at every node" << std::endl;
            break;
        }
        case 5: {
            int value;
            std::cout << "Enter the value to search for: ";
            std::cin >> value;
            bool found = tree.search(value);
            if (found) {
                std::cout << "The value " << value << " is in the tree" << std::endl;
            }
            else {
                std::cout << "The value " << value << " is not in the tree" << std::endl;
            }
            break;
        }
        case 6: {
            int value;
            std::cout << "Enter the value to delete: ";
            std::cin >> value;
            tree.remove(value);
            break;
        }
        case 7:
            std::cout << "Exiting program..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 6." << std::endl;
        }
    } while (choice != 7);

    return 0;
}

