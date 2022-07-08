#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Graph {
    private:
        int V;
        list<int> *adj;
    
    public:
        Graph(int V) {
            this->V = V;
            adj = new list<int>[V];
        }
        ~Graph() { delete [] adj; }
        void DFS(int v, bool visited[]);
        Graph transpose();
        void addEdge(vector <pair<int, int> > adj[], int u, int v, int wt);
        bool isStronglyConnected();
        void addRandomEdge(vector <pair<int, int> > adj[]);
};

// DFS traversal for visiting nodes
void Graph::DFS(int v, bool visited[]) {
    visited[v] = true;
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFS(*i, visited);
}

// Reverse all edges
Graph Graph::transpose() {
    Graph graph(V);
    for (int v = 0; v < V; v++) {
      list<int>::iterator i;
      for(i = adj[v].begin(); i != adj[v].end(); ++i)
         graph.adj[*i].push_back(v);
   }
   return graph;
}

// To add an edge
void Graph::addEdge(vector <pair<int, int> > adj[], int u, int v, int wt) {
    adj[u].push_back(make_pair(v, wt));
}

// Print adjacency list representation of graph
void printGraph(vector<pair<int,int> > adj[], int V) {
    int v, wt;
    for (int u = 0; u < V; u++)
    {
        for (auto it = adj[u].begin(); it!=adj[u].end(); it++)
        {
            v = it->first;
            wt = it->second;
            cout << u <<" -> " << "(" << u << ", " << v << ", " << wt << ")";
            cout << "\t";
        }
        cout << "\n";
    }
    cout << "\n\n";
}

// Function 1
// To check if graph is strongly connected
bool Graph::isStronglyConnected() {
    bool visited[V];
    for (int i = 0; i < V; i++)
            visited[i] = false;

    DFS(0, visited);
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            return false;
    
    Graph graph = transpose();
    for(int i = 0; i < V; i++)
        visited[i] = false;

    graph.DFS(0, visited);
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            return false;
    
    return true;
}

// To add random edges
void Graph::addRandomEdge(vector <pair<int, int> > adj[]) {
    int wt;
    int u = rand()%5;
    int v = rand()%5;
    adj[u].push_back(make_pair(v, wt));
}
 
// Main function
int main()
{
    int V = 5;
    Graph graph(V);
    vector<pair<int, int> > adj[V];
    graph.addEdge(adj, 0, 1, 7009);
    graph.addEdge(adj, 1, 2, 5234);
    graph.addEdge(adj, 2, 3, 1381);
    graph.addEdge(adj, 3, 4, 2107);
    graph.addEdge(adj, 4, 0, 1495);

    cout << "Default graph:\n";
    printGraph(adj, V);

    if (graph.isStronglyConnected() == true)
        cout << "\nThis graph is strongly connected." << endl;
    else {
        cout << "\nThis graph is not strongly connected." << endl;
        for (int i = 0; i < V; i++) {
        	graph.addRandomEdge(adj);
		}
        cout << "New graph:\n";
        printGraph(adj, V);
    }
    
    return 0;
}