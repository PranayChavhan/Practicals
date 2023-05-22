#include <iostream>
#include <vector>
#include <queue>
#include <limits.h> // Include the limits header for INT_MAX

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph {
    int V; // Number of vertices
    int E; // Number of edges

    vector<Edge> edges; // Vector to store edges

    Graph(int v, int e) {
        V = v;
        E = e;
    }
};

// Function to add an edge to the graph
void addEdge(Graph& graph, int src, int dest, int weight) {
    Edge edge;
    edge.src = src;
    edge.dest = dest;
    edge.weight = weight;
    graph.edges.push_back(edge);
}

// Function to find the minimum cost spanning tree using Prim's algorithm
int primMST(Graph& graph) {
    // Priority queue to store vertices and their key values
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    int src = 0; // Start from the first vertex

    // Create a vector for keys and initialize all key values as infinite
    vector<int> key(graph.V, INT_MAX);

    // Create a vector to store the parent of each vertex in the MST
    vector<int> parent(graph.V, -1);

    // Create a vector to track whether a vertex is included in MST or not
    vector<bool> inMST(graph.V, false);

    // Insert the source vertex into the priority queue and initialize its key as 0
    pq.push(make_pair(0, src));
    key[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        // Iterate through all adjacent vertices of u
        for (auto& edge : graph.edges) {
            int v = (edge.src == u) ? edge.dest : edge.src;
            int weight = edge.weight;

            // If v is not yet included in MST and weight of (u,v) is smaller than the current key of v
            if (inMST[v] == false && weight < key[v]) {
                // Update the key value of v
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    // Calculate the total cost by summing up the key values of all vertices (excluding the source vertex)
    int totalCost = 0;
    for (int i = 1; i < graph.V; i++) {
        totalCost += key[i];
    }

    return totalCost;
}

int main() {
    int numOffices, numConnections;
    cout << "Enter the number of offices: ";
    cin >> numOffices;

    cout << "Enter the number of connections: ";
    cin >> numConnections;

    Graph graph(numOffices, numConnections);

    for (int i = 0; i < numConnections; i++) {
        int src, dest, weight;
        cout << "Enter connection " << (i + 1) << " (source destination weight): ";
        cin >> src >> dest >> weight;
        addEdge(graph, src, dest, weight);
    }

    int minCost = primMST(graph);
    cout << "Minimum cost to connect all offices: " << minCost << endl;

    return 0;
}
