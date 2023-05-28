#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
using namespace std;

class Graph {
private:
    map<string, vector<string>> adjacencyList;

public:
    void addNode(const string& node) {
        adjacencyList[node] = vector<string>();
    }

    void addEdge(const string& source, const string& destination) {
        adjacencyList[source].push_back(destination);
        adjacencyList[destination].push_back(source); // Uncomment for an undirected graph
    }

    void dfs(const string& startNode) {
        map<string, bool> visited;
        dfsHelper(startNode, visited);
    }

    void bfs(const string& startNode) {
        map<string, bool> visited;
        queue<string> queue;

        visited[startNode] = true;
        queue.push(startNode);

        while (!queue.empty()) {
            string currentNode = queue.front();
            queue.pop();

            cout << currentNode << " ";

            for (const string& neighbor : adjacencyList[currentNode]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }
    }

private:
    void dfsHelper(const string& currentNode, map<string, bool>& visited) {
        visited[currentNode] = true;
        cout << currentNode << " ";

        for (const string& neighbor : adjacencyList[currentNode]) {
            if (!visited[neighbor]) {
                dfsHelper(neighbor, visited);
            }
        }
    }
};

int main() {
    Graph graph;

    // Add nodes (landmarks)
    graph.addNode("A");
    graph.addNode("B");
    graph.addNode("C");
    graph.addNode("D");
    graph.addNode("E");

    // Add edges (connections between landmarks)
    graph.addEdge("A", "B");
    graph.addEdge("A", "C");
    graph.addEdge("B", "D");
    graph.addEdge("C", "D");
    graph.addEdge("C", "E");

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
                string startNode;
                cout << "Enter the starting node for DFS: ";
                cin >> startNode;
                cout << "DFS traversal: ";
                graph.dfs(startNode);
                cout << endl;
                break;
            }
            case 2: {
                string startNode;
                cout << "Enter the starting node for BFS: ";
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
