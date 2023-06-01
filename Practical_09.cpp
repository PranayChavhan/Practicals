#include <iostream>
#include <string>

using namespace std;

class Node {
public:
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

class Dictionary {
private:
    Node* root;

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

    Node* insertKeyword(Node* node, string key, string meaning) {
        if (node == nullptr) {
            return new Node(key, meaning);
        }

        if (key < node->keyword) {
            node->left = insertKeyword(node->left, key, meaning);
        } else if (key > node->keyword) {
            node->right = insertKeyword(node->right, key, meaning);
        } else {
            node->meaning = meaning;
            return node;
        }

        node = balanceTree(node, key);

        return node;
    }


    Node* findMinNode(Node* node) {
        if (node == nullptr || node->left == nullptr) {
            return node;
        }
        return findMinNode(node->left);
    }

    Node* deleteKeyword(Node* node, string key) {
        if (node == nullptr) {
            return node;
        }

        if (key < node->keyword) {
            node->left = deleteKeyword(node->left, key);
        } else if (key > node->keyword) {
            node->right = deleteKeyword(node->right, key);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node* successor = findMinNode(node->right);
                node->keyword = successor->keyword;
                node->meaning = successor->meaning;
                node->right = deleteKeyword(node->right, successor->keyword);
            }
        }

        if (node == nullptr) {
            return node;
        }

        node = balanceTree(node, key);

        return node;
    }

    Node* updateKeyword(Node* node, string key, string newMeaning) {
        if (node == nullptr) {
            return node;
        }

        if (key < node->keyword) {
            node->left = updateKeyword(node->left, key, newMeaning);
        } else if (key > node->keyword) {
            node->right = updateKeyword(node->right, key, newMeaning);
        } else {
            node->meaning = newMeaning;
        }

        return node;
    }

    void displayAscending(Node* node) {
        if (node != nullptr) {
            displayAscending(node->left);
            cout << node->keyword << " : " << node->meaning << endl;
            displayAscending(node->right);
        }
    }

    void displayDescending(Node* node) {
        if (node != nullptr) {
            displayDescending(node->right);
            cout << node->keyword << " : " << node->meaning << endl;
            displayDescending(node->left);
        }
    }

    Node* searchKeyword(Node* node, string key, int& comparisons) {
        if (node == nullptr || node->keyword == key) {
            return node;
        }

        comparisons++;

        if (key < node->keyword) {
            return searchKeyword(node->left, key, comparisons);
        } else {
            return searchKeyword(node->right, key, comparisons);
        }
    }

public:
    Dictionary() {
        root = nullptr;
    }

    void addKeyword(string key, string meaning) {
        root = insertKeyword(root, key, meaning);
    }

    void deleteKeyword(string key) {
        root = deleteKeyword(root, key);
    }

    void updateKeyword(string key, string newMeaning) {
        root = updateKeyword(root, key, newMeaning);
    }

    void displayAscendingOrder() {
        cout << "Dictionary (Ascending Order):" << endl;
        displayAscending(root);
    }

    void displayDescendingOrder() {
        cout << "Dictionary (Descending Order):" << endl;
        displayDescending(root);
    }

    string searchKeyword(string key) {
        int comparisons = 0;
        Node* result = searchKeyword(root, key, comparisons);
        if (result != nullptr) {
            return result->meaning;
        } else {
            return "Keyword not found!";
        }
    }
};

int main() {
    Dictionary dict;

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
                    dict.addKeyword(keyword, meaning);
                    cout << "Keyword added successfully!" << endl;
                    break;
                }
            case 2:
                {
                    string keyword;
                    cout << "Enter the keyword to delete: ";
                    cin >> keyword;
                    dict.deleteKeyword(keyword);
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
                    dict.updateKeyword(keyword, newMeaning);
                    cout << "Keyword updated successfully!" << endl;
                    break;
                }
            case 4:
                dict.displayAscendingOrder();
                break;
            case 5:
                dict.displayDescendingOrder();
                break;
            case 6:
                {
                    string keyword;
                    cout << "Enter the keyword to find: ";
                    cin >> keyword;
                    string meaning = dict.searchKeyword(keyword);
                    cout << "Meaning: " << meaning << endl;
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
