#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Structure to represent a node in the binary search tree
struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) {
        key = k;
        left = nullptr;
        right = nullptr;
    }
};

// Function to calculate the sum of probabilities between indices i and j
double sumProbabilities(const vector<double>& probabilities, int i, int j) {
    double sum = 0;
    for (int k = i; k <= j; k++) {
        sum += probabilities[k];
    }
    return sum;
}

// Function to construct the optimal binary search tree
Node* constructOptimalBST(const vector<int>& keys, const vector<double>& probabilities) {
    int n = keys.size();

    // Create a 2D table to store the costs
    vector<vector<double>> cost(n + 1, vector<double>(n + 1, 0));

    // Create a 2D table to store the optimal subtree roots
    vector<vector<Node*>> root(n, vector<Node*>(n, nullptr));

    // Initialize the diagonal elements of the cost table
    for (int i = 0; i < n; i++) {
        cost[i][i] = probabilities[i];
        root[i][i] = new Node(keys[i]);
    }

    // Fill the cost and root tables diagonally
    for (int L = 2; L <= n; L++) {
        for (int i = 0; i <= n - L + 1; i++) {
            int j = i + L - 1;
            cost[i][j] = numeric_limits<double>::max(); // Initialize cost to maximum

            // Calculate the optimal root and cost for the current subtree
            for (int r = i; r <= j; r++) {
                double c = ((r > i) ? cost[i][r - 1] : 0) + ((r < j) ? cost[r + 1][j] : 0) + sumProbabilities(probabilities, i, j);

                if (c < cost[i][j]) {
                    cost[i][j] = c;
                    root[i][j] = new Node(keys[r]);
                }
            }
        }
    }

    return root[0][n - 1]; // Return the root of the optimal binary search tree
}

// Function to perform inorder traversal of the binary search tree
void inorderTraversal(Node* root) {
    if (root) {
        inorderTraversal(root->left);
        cout << root->key << " ";
        inorderTraversal(root->right);
    }
}

int main() {
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;

    vector<int> keys(n);
    vector<double> probabilities(n);

    cout << "Enter the keys: ";
    for (int i = 0; i < n; i++) {
        cin >> keys[i];
    }

    cout << "Enter the probabilities: ";
    for (int i = 0; i < n; i++) {
        cin >> probabilities[i];
    }

    Node* root = constructOptimalBST(keys, probabilities);

    cout << "Optimal Binary Search Tree (Inorder Traversal): ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}
