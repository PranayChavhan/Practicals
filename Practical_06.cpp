#include <iostream>
#include <queue>
#include <map>
#include <string>
using namespace std;

const int MAX_NODES = 10;

class Graph {
private:
    int adjacencyList[MAX_NODES][MAX_NODES];
    map<int, string> nodeNames;
    int numNodes;

public:
    Graph() {
        for (int i = 0; i < MAX_NODES; i++) {
            for (int j = 0; j < MAX_NODES; j++) {
                adjacencyList[i][j] = 0;
            }
        }
        numNodes = 0;
    }

    void addNode(const string& nodeName) {
        nodeNames[numNodes] = nodeName;
        numNodes++;
    }

    void addEdge(int source, int destination) {
        adjacencyList[source][destination] = 1;
        adjacencyList[destination][source] = 1; // Uncomment for an undirected graph
    }

    void dfs(int startNode) {
        map<int, bool> visited;
        dfsHelper(startNode, visited);
    }

    void bfs(int startNode) {
        map<int, bool> visited;
        queue<int> queue;

        visited[startNode] = true;
        queue.push(startNode);

        while (!queue.empty()) {
            int currentNode = queue.front();
            queue.pop();

            cout << nodeNames[currentNode] << " ";

            for (int neighbor = 0; neighbor < numNodes; neighbor++) {
                if (adjacencyList[currentNode][neighbor] == 1 && !visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }
    }

private:
    void dfsHelper(int currentNode, map<int, bool>& visited) {
        visited[currentNode] = true;
        cout << nodeNames[currentNode] << " ";

        for (int neighbor = 0; neighbor < numNodes; neighbor++) {
            if (adjacencyList[currentNode][neighbor] == 1 && !visited[neighbor]) {
                dfsHelper(neighbor, visited);
            }
        }
    }
};

int main() {
    Graph graph;

    // Add nodes (landmarks)
    graph.addNode("Park");
    graph.addNode("Library");
    graph.addNode("Cafeteria");
    graph.addNode("Sports Complex");
    graph.addNode("Auditorium");

    // Add edges (connections between landmarks)
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);

    int choice;
    do {
        cout << "Graph Menu:" << endl;
        cout << "1. Perform DFS" << endl;
        cout << "2. Perform BFS" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int startNode;
                cout << "Enter the starting node for DFS (0-" << graph.getNumNodes() - 1 << "): ";
                cin >> startNode;
                cout << "DFS traversal: ";
                graph.dfs(startNode);
                cout << endl;
                break;
            }
            case 2: {
                int startNode;
                cout << "Enter the starting node for BFS (0-" << graph.getNumNodes() - 1 << "): ";
                cin >> startNode;
                cout << "BFS traversal: ";
                graph.bfs(startNode);
                cout << endl;
                break;
            }
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << endl;
    } while (choice != 3);

    return 0;
}
