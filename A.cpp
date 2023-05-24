#include <iostream>
#include <limits>

using namespace  std;

const int MAX_OFFICES = 10;

class Graph{
    private:
    int numOfOffices;
    int adjacencyMatrix[MAX_OFFICES][MAX_OFFICES];

    public:
    Graph(int offices){
        numOfOffices = offices;

        for (int i = 0; i < numOfOffices; ++i)
        {
            for(int j = 0; j < numOfOffices; ++j){
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int src, int dest, int cost){
        adjacencyMatrix[src][dest] = cost;
        adjacencyMatrix[dest][src] = cost;

    }

    void displayMatrix(){
        cout<< "Adjacency Matrix: "<<endl;

        for(int i = 0; i < numOfOffices; ++i){
            for (int j = 0; j < numOfOffices; ++j)
            {
                cout<<adjacencyMatrix[i][j]<<"\t";

            }
            cout << endl;
            
        }
    }


    int primMST(){
        int key[MAX_OFFICES];
        bool inMST[MAX_OFFICES];
        int parent[MAX_OFFICES];

        for (int i = 0; i < numOfOffices; ++i)
        {
            key[i] = numeric_limits<int>::max();
            inMST[i] = false;
        }

        key[0] = 0;

        int totalCost = 0;

        for (int count = 0; count < numOfOffices; ++count)
        {
            int minKey = numeric_limits<int>::max();
            int minIndex;


            for (int v = 0; v < numOfOffices; ++v)
            {
                if (!inMST[v] && key[v] < minKey)
                {
                    minKey = key[v];
                    minIndex = v;
                }
                
            }
            int u = minIndex;
            inMST[u] = true;


            totalCost += key[u];


            for (int v = 0; v < numOfOffices; ++v)
            {
                if(adjacencyMatrix[u][v] && !inMST[v] && adjacencyMatrix[u][v] < key[v]){
                    key[v] = adjacencyMatrix[u][v];
                    parent[v] = u;
                }
                
            }
            
        }
        return totalCost;
        
        
    }
};

int main(){
    int numOfOffices, numOfConnections;
    cout<< "Enter the number of offices: ";
    cin>> numOfOffices;

    cout << "Enter the number of connections: ";
    cin >> numOfConnections;

    Graph graph(numOfOffices);
    for (int i = 0; i < numOfConnections; ++i) {
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