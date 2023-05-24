#include<iostream>
using namespace std;

class OptimalBST {
private:
    int numKeys;
    float *successProbabilities;
    float *failureProbabilities;
    float **weightTable;
    float **costTable;
    int **rootTable;

public:
    OptimalBST(int numNodes) {
        numKeys = numNodes;
        successProbabilities = new float[numKeys + 1];
        failureProbabilities = new float[numKeys + 1];
        weightTable = new float*[numKeys + 2];
        costTable = new float*[numKeys + 1];
        rootTable = new int*[numKeys + 1];

        for (int i = 0; i <= numKeys + 2; i++) {
            weightTable[i] = new float[numKeys + 1];
        }

        for (int i = 0; i <= numKeys; i++) {
            costTable[i] = new float[numKeys + 1];
            rootTable[i] = new int[numKeys + 1];
        }
    }

    ~OptimalBST() {
        delete[] successProbabilities;
        delete[] failureProbabilities;

        for (int i = 0; i <= numKeys + 2; i++) {
            delete[] weightTable[i];
        }

        for (int i = 0; i <= numKeys; i++) {
            delete[] costTable[i];
            delete[] rootTable[i];
        }

        delete[] weightTable;
        delete[] costTable;
        delete[] rootTable;
    }

    void readProbabilities() {
        cout << "\nEnter the probability for successful search:\n";
        for (int i = 1; i <= numKeys; i++) {
            cout << "P[" << i << "]: ";
            cin >> successProbabilities[i];
        }

        cout << "\nEnter the probability for unsuccessful search:\n";
        for (int i = 0; i <= numKeys; i++) {
            cout << "Q[" << i << "]: ";
            cin >> failureProbabilities[i];
        }
    }

    void constructOptimalBST() {
        for (int i = 0; i <= numKeys; i++) {
            weightTable[i][i] = failureProbabilities[i];
            costTable[i][i] = 0;
            rootTable[i][i] = 0;
        }

        for (int length = 1; length <= numKeys; length++) {
            for (int i = 0; i <= numKeys - length + 1; i++) {
                int j = i + length - 1;
                weightTable[i][j] = weightTable[i][j - 1] + successProbabilities[j] + failureProbabilities[j];
                costTable[i][j] = -1;

                for (int k = i; k <= j; k++) {
                    float cost = (k > i ? costTable[i][k - 1] : 0) + (k < j ? costTable[k + 1][j] : 0) + weightTable[i][j];

                    if (costTable[i][j] == -1 || cost < costTable[i][j]) {
                        costTable[i][j] = cost;
                        rootTable[i][j] = k;
                    }
                }
            }
        }
    }

    void printOptimalBST() {
        cout << "\nOptimal Binary Search Tree (Inorder Traversal):\n";
        printInorderTraversal(1, numKeys);
        cout << endl;
    }

private:
    void printInorderTraversal(int start, int end) {
        if (start > end) {
            return;
        }

        int root = rootTable[start][end];
        cout << "Key " << root << " ";

        printInorderTraversal(start, root - 1);
        printInorderTraversal(root + 1, end);
    }
};

int main() {
    int numKeys;
    cout << "*** PROGRAM FOR OPTIMAL BINARY SEARCH TREE ***" << endl;
    cout << "\nEnter the number of keys: ";
    cin >> numKeys;

    OptimalBST optimalBST(numKeys);
    optimalBST.readProbabilities();
    optimalBST.constructOptimalBST();
    optimalBST.printOptimalBST();

    return 0;
}
