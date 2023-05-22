#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    string keyword;
    string meaning;
    int height;
    Node* left;
    Node* right;

    Node(string key, string val) {
        keyword = key;
        meaning = val;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

int getHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int getBalanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

void updateHeight(Node* node) {
    if (node == nullptr) {
        return;
    }
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* balanceTree(Node* node, string key) {
    updateHeight(node);

    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1 && key < node->left->keyword) {
        return rightRotate(node);
    }

    if (balanceFactor < -1 && key > node->right->keyword) {
        return leftRotate(node);
    }

    if (balanceFactor > 1 && key > node->left->keyword) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balanceFactor < -1 && key < node->right->keyword) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* insertKeyword(Node* root, string key, string meaning) {
    if (root == nullptr) {
        return new Node(key, meaning);
    }

    if (key < root->keyword) {
        root->left = insertKeyword(root->left, key, meaning);
    } else if (key > root->keyword) {
        root->right = insertKeyword(root->right, key, meaning);
    } else {
        root->meaning = meaning;
        return root;
    }

    root = balanceTree(root, key);

    return root;
}

Node* findMinNode(Node* node) {
    if (node == nullptr || node->left == nullptr) {
        return node;
    }
    return findMinNode(node->left);
}

Node* deleteKeyword(Node* root, string key) {
    if (root == nullptr) {
        return root;
    }

    if (key < root->keyword) {
        root->left = deleteKeyword(root->left, key);
    } else if (key > root->keyword) {
        root->right = deleteKeyword(root->right, key);
    } else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* successor = findMinNode(root->right);
            root->keyword = successor->keyword;
            root->meaning = successor->meaning;
            root->right = deleteKeyword(root->right, successor->keyword);
        }
    }

    if (root == nullptr) {
        return root;
    }

    root = balanceTree(root, key);

    return root;
}

Node* updateKeyword(Node* root, string key, string newMeaning) {
    if (root == nullptr) {
        return root;
    }

    if (key < root->keyword) {
        root->left = updateKeyword(root->left, key, newMeaning);
    } else if (key > root->keyword) {
        root->right = updateKeyword(root->right, key, newMeaning);
    } else {
        root->meaning = newMeaning;
    }

    return root;
}

void displayAscending(Node* root) {
    if (root != nullptr) {
        displayAscending(root->left);
        cout << root->keyword << " : " << root->meaning << endl;
        displayAscending(root->right);
    }
}

void displayDescending(Node* root) {
    if (root != nullptr) {
        displayDescending(root->right);
        cout << root->keyword << " : " << root->meaning << endl;
        displayDescending(root->left);
    }
}

Node* searchKeyword(Node* root, string key, int& comparisons) {
    if (root == nullptr || root->keyword == key) {
        return root;
    }

    comparisons++;

    if (key < root->keyword) {
        return searchKeyword(root->left, key, comparisons);
    } else {
        return searchKeyword(root->right, key, comparisons);
    }
}

int main() {
    Node* root = nullptr;

    while (true) {
        cout << "Dictionary Menu:" << endl;
        cout << "1. Add a keyword" << endl;
        cout << "2. Delete a keyword" << endl;
        cout << "3. Update a keyword" << endl;
        cout << "4. Display dictionary in ascending order" << endl;
        cout << "5. Display dictionary in descending order" << endl;
        cout << "6. Find a keyword" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                {
                    string keyword, meaning;
                    cout << "Enter the keyword: ";
                    cin >> keyword;
                    cout << "Enter the meaning: ";
                    cin.ignore();
                    getline(cin, meaning);
                    root = insertKeyword(root, keyword, meaning);
                    cout << "Keyword added successfully!" << endl;
                    break;
                }
            case 2:
                {
                    string keyword;
                    cout << "Enter the keyword to delete: ";
                    cin >> keyword;
                    root = deleteKeyword(root, keyword);
                    cout << "Keyword deleted successfully!" << endl;
                    break;
                }
            case 3:
                {
                    string keyword, newMeaning;
                    cout << "Enter the keyword to update: ";
                    cin >> keyword;
                    cout << "Enter the new meaning: ";
                    cin.ignore();
                    getline(cin, newMeaning);
                    root = updateKeyword(root, keyword, newMeaning);
                    cout << "Keyword updated successfully!" << endl;
                    break;
                }
            case 4:
                cout << "Dictionary (Ascending Order):" << endl;
                displayAscending(root);
                break;
            case 5:
                cout << "Dictionary (Descending Order):" << endl;
                displayDescending(root);
                break;
            case 6:
                {
                    string keyword;
                    cout << "Enter the keyword to find: ";
                    cin >> keyword;
                    int comparisons = 0;
                    Node* result = searchKeyword(root, keyword, comparisons);
                    if (result != nullptr) {
                        cout << "Meaning: " << result->meaning << endl;
                        cout << "Number of comparisons: " << comparisons << endl;
                    } else {
                        cout << "Keyword not found!" << endl;
                    }
                    break;
                }
            case 7:
                cout << "Exiting... Thank you!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }
}
