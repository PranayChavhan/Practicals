#include <iostream>

using namespace std;

class Node {
public:
    int key;
    int frequency;
    Node* left;
    Node* right;

    Node(int key, int frequency) {
        this->key = key;
        this->frequency = frequency;
        left = right = nullptr;
    }
};

class OBST {
private:
    int* keys;
    int* frequencies;
    int n;
    Node** cost;
    Node** root;

public:
    OBST(int* keys, int* frequencies, int n) {
        this->keys = keys;
        this->frequencies = frequencies;
        this->n = n;

        cost = new Node*[n + 1];
        root = new Node*[n + 1];
        for (int i = 0; i <= n; i++) {
            cost[i] = new Node[n + 1];
            root[i] = new Node[n + 1];
        }
    }

    void constructOBST() {
        for (int i = 0; i < n; i++) {
            cost[i][i] = Node(keys[i], frequencies[i]);
            cost[i][i].frequency = frequencies[i];
        }

        for (int L = 2; L <= n; L++) {
            for (int i = 0; i <= n - L + 1; i++) {
                int j = i + L - 1;
                cost[i][j].frequency = INT_MAX;

                for (int r = i; r <= j; r++) {
                    int frequencySum = getFrequencySum(i, j);
                    int c = ((r > i) ? cost[i][r - 1].frequency : 0) +
                            ((r < j) ? cost[r + 1][j].frequency : 0) + frequencySum;

                    if (c < cost[i][j].frequency) {
                        cost[i][j].frequency = c;
                        cost[i][j].key = keys[r];
                        cost[i][j].left = ((r > i) ? &cost[i][r - 1] : nullptr);
                        cost[i][j].right = ((r < j) ? &cost[r + 1][j] : nullptr);
                    }
                }
            }
        }
    }

    int getFrequencySum(int i, int j) {
        int sum = 0;
        for (int k = i; k <= j; k++)
            sum += frequencies[k];
        return sum;
    }

    void printOBST() {
        cout << "Optimal Binary Search Tree:" << endl;
        printOBSTUtil(0, n - 1, 0);
    }

    void printOBSTUtil(int start, int end, int level) {
        if (start > end)
            return;

        if (start == end) {
            cout << "Level " << level << ": ";
            cout << "(" << keys[start] << ") " << endl;
            return;
        }

        int key = cost[start][end].key;
        cout << "Level " << level << ": ";
        cout << "(" << key << ") " << endl;

        int i = findKeyIndex(key);
        printOBSTUtil(start, i - 1, level + 1);
        printOBSTUtil(i + 1, end, level + 1);
    }

    int findKeyIndex(int key) {
        for (int i = 0; i < n; i++) {
            if (keys[i] == key)
                return i;
        }
        return -1;
    }

    ~OBST() {
        for (int i = 0; i <= n; i++) {
            delete[] cost[i];
            delete[] root[i];
        }
        delete[] cost;
        delete[] root;
    }
};

int main() {
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;

    int* keys = new int[n];
    int* frequencies = new int[n];

    cout << "Enter the keys:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> keys[i];
    }

    cout << "Enter the frequencies:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> frequencies[i];
    }

    OBST obst(keys, frequencies, n);
    obst.constructOBST();
    obst.printOBST();

    delete[] keys;
    delete[] frequencies;

    return 0;
}
