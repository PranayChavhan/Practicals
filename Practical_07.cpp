#include <iostream>
#include <limits>

using namespace std;

const int MAX_OFFICES = 10; // Maximum number of offices

// Class to represent a graph
class Graph {
private:
    int numOffices;
    int adjacencyMatrix[MAX_OFFICES][MAX_OFFICES];

public:
    Graph(int offices) {
        numOffices = offices;

        // Initialize the adjacency matrix with 0 (no edge)
        for (int i = 0; i < numOffices; ++i) {
            for (int j = 0; j < numOffices; ++j) {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int src, int dest, int cost) {
        // Since the graph is undirected, set both src->dest and dest->src with the same cost
        adjacencyMatrix[src][dest] = cost;
        adjacencyMatrix[dest][src] = cost;
    }

    void displayMatrix() {
        cout << "Adjacency Matrix:" << endl;
        for (int i = 0; i < numOffices; ++i) {
            for (int j = 0; j < numOffices; ++j) {
                cout << adjacencyMatrix[i][j] << "\t";
            }
            cout << endl;
        }
    }

    int primMST() {
        int key[MAX_OFFICES];
        bool inMST[MAX_OFFICES];
        int parent[MAX_OFFICES];

        // Initialize key values and MST sets
        for (int i = 0; i < numOffices; ++i) {
            key[i] = numeric_limits<int>::max();
            inMST[i] = false;
        }

        key[0] = 0; // Start with the first vertex

        int totalCost = 0;

        // Find the minimum cost spanning tree
        for (int count = 0; count < numOffices - 1; ++count) {
            int minKey = numeric_limits<int>::max();
            int minIndex;

            // Find the vertex with the minimum key value that is not yet included in MST
            for (int v = 0; v < numOffices; ++v) {
                if (!inMST[v] && key[v] < minKey) {
                    minKey = key[v];
                    minIndex = v;
                }
            }

            int u = minIndex;
            inMST[u] = true;

            // Add the cost of the selected edge to the total cost
            totalCost += key[u];

            // Update the key values of adjacent vertices
            for (int v = 0; v < numOffices; ++v) {
                if (adjacencyMatrix[u][v] && !inMST[v] && adjacencyMatrix[u][v] < key[v]) {
                    key[v] = adjacencyMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        return totalCost;
    }
};

int main() {
    int numOffices, numConnections;
    cout << "Enter the number of offices: ";
    cin >> numOffices;

    cout << "Enter the number of connections: ";
    cin >> numConnections;

    Graph graph(numOffices);

    for (int i = 0; i < numConnections; ++i) {
        int src, dest, cost;
        cout << "Enter connection " << (i + 1) << " (source destination cost): ";
        cin >> src >> dest >> cost;
        graph.addEdge(src, dest, cost);
    }

    graph.displayMatrix();

    int minCost = graph.primMST();
    cout << "Minimum cost to connect all offices: " << minCost << endl;

    return 0;
}
