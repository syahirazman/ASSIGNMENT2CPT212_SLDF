#include <bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f

class Graph {
	
   int V;
   list<pair<int, int>> *adj;
   void isSCUtil(int u, bool visited[]);		// A recursive function to print DFS starting from v
   bool isCyclicUtil(int v, bool visited[], bool *recurStack);		// A recursive function to print DFS starting from v
   
   public:
	// Constructor	
   Graph(int V) {
      this->V = V;
      adj = new list<pair<int,int>>[V];
   }
   
   // Destructor
   ~Graph() {
      delete [] adj;
   }
   
   void addEdge(int u, int v, int w);	// To add a new edge
   void printGraph();	// To print graph
   bool isStronglyConnected();	// To check whether graph is strongly connected
   bool isCyclic();		// To check whether graph contains cycle
   Graph transpose();	// To create a reverse graph
   void shortestPath(int u, int v); // To output shortest path between source and destination
};


// Recursive function to print DFS starting from v used by isStronglyConnected()
void Graph::isSCUtil(int v, bool visited[]) {
   visited[v] = true;
   for(int i=0; i< sizeof(adj[v])/sizeof(int);i++)
   		if (!visited[i])
		   isSCUtil(i, visited);
}

// Recursive function to print DFS starting from v used by isCyclic()
bool Graph::isCyclicUtil(int v, bool visited[], bool *recurStack)
{
    if(visited[v] == false)
    {
        visited[v] = true;
        recurStack[v] = true;
        
        //list<pair<int,int>>::iterator i;
        for(int i=0; i< sizeof(adj[v])/sizeof(int);i++)
        {
        	if ( !visited[i] && isCyclicUtil(i, visited, recurStack) )
                return true;
            else if (recurStack[i])
                return true; 
        }
    }
    recurStack[v] = false; // Remove vertex from recursion stack
    return false;
}

// Function to reverse graph used by isStronglyConnected()
Graph Graph::transpose() {
   Graph g(V);
   int wt;
   for (int v = 0; v < V; v++) {
   		//list<pair<int,int>>::iterator i;
      	for(int i = 0; i < adj[v].size(); ++i)
        	g.adj[i].push_back(make_pair(v, wt));
   }
   return g;
}

// Function to add new edge into adjacency list used by main()
void Graph::addEdge(int u, int v, int w) {
   adj[u].push_back(make_pair(v, w));
}

// Function to print the resulting adjacency list used by main()
void Graph::printGraph() {
	int v, w;
	for (int u = 0; u < V; u++) {
		cout << "\t\t\t     " << u;
		for (auto i = adj[u].begin(); i!=adj[u].end(); ++i)
        {
            v = i->first;
            w = i->second;
            cout << " -> (" << v << ", " << w << ")";
        }
        cout << endl;
	}
	cout << endl;
}

// Function 1
// Function that returns true if graph is strongly connected
bool Graph::isStronglyConnected() {
   bool visited[V];
   for (int i = 0; i < V; i++)
   		visited[i] = false;
   	
   isSCUtil(0, visited);
   
   for (int i = 0; i < V; i++)
      if (visited[i] == false)
         return false;
         
   Graph gr = transpose();
   
   for(int i = 0; i < V; i++)
      visited[i] = false;
	
   gr.isSCUtil(0, visited);
   for (int i = 0; i < V; i++)
      if (visited[i] == false)
         return false;
         
   return true;
}


// Function 2
// Function that returns true if graph contains cycle
bool Graph::isCyclic()
{
    bool *visited = new bool[V];
    bool *recurStack = new bool[V];
    for(int i = 0; i < V; i++)
    {
        visited[i] = false;
        recurStack[i] = false;
    }
  
    for(int i = 0; i < V; i++)
        if ( !visited[i] && isCyclicUtil(i, visited, recurStack))
            return true;
  
    return false;
}

// Function 3
// Function that prints shortest path between two vertices from user inputs
void Graph::shortestPath(int src, int dest) {
	
	set<pair<int,int>> setds;
	vector<int> dist(V,INF);
	setds.insert(make_pair(0, src));
    dist[src] = 0;
    while (!setds.empty())
    {
        pair<int, int> temp = *(setds.begin());
        setds.erase(setds.begin());
 
        int u = temp.second;
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = i->first;
            int w = i->second;
 
            if (dist[v] > dist[u] + w)
            {
                if (dist[v] != INF)
                    setds.erase(setds.find(make_pair(dist[v], v)));
                    
                dist[v] = dist[u] + w;
                setds.insert(make_pair(dist[v], v));
            }
        }
    }
    cout << "\n\t\t     Shortest path from " << src << " to " << dest << ": " << dist[dest] << endl;
}
	
int main() {
   
   Graph graph(5);
   
   cout << "\n\n\n\n\n";
   cout << "\t\t\t\t\t\tWELCOME\n\n";
   cout << "\t\tThis program displays the default graph in the form of adjacency list.\n";
   cout << "\tThe graph consists of 5 cities represented by integer 0 to 4 and the distance between connected cities.\n\n";
   cout << "\t\t\t\t    The cities are:\n";
   cout << "\t\t\t\t    0 - \t Dublin, Ireland\n";
   cout << "\t\t\t\t    1 - \t Kigali, Rwanda\n";
   cout << "\t\t\t\t    2 - \t Split, Croatia\n";
   cout << "\t\t\t\t    3 - \t Copenhagen, Denmark\n";
   cout << "\t\t\t\t    4 - \t Raykjavik, Iceland\n";
   cout << "\n\n\n\n\n";
   cout << "\t\t   This program will do the following on the default graph:\n";
   cout << "\t\t   1: \t Check if the graph is strongly connected.\n";
   cout << "\t\t   2: \t Check if the graph contains any cycle.\n";
   cout << "\t\t   3: \t Find the shortest path betweent two cities.\n";
   cout << "\t\t   3: \t Find the minimum spanning tree between several cities.\n";
   
   char start;
   cout << "\n\n\n\n\n";
   cout << "\t\t   Enter Y to start: ";
   cin >> start;
   
   // creating the default graph
   if (start=='y' || start=='Y') {
   		system("CLS");
   		cout << "\n\n\n\n\n";
   		cout << "\t\t     Program is building the default graph. . .\n";
		
		graph.addEdge(0, 1, 7009);
		graph.addEdge(1, 2, 5234);
		graph.addEdge(2, 3, 1381);
		graph.addEdge(3, 4, 2107);
		graph.addEdge(4, 0, 1495);
   		
		cout << "\n\t\t     " << system("PAUSE");
   		cout << "\n\n\n";
   		graph.printGraph();
   }
   
   char proceed;
   cout << "\n\n\n\n\n";
   cout << "\t\t     Enter P to proceed to the next step: ";
   cin >> proceed;
   
   // checking connectivity
   if (proceed=='p' || proceed=='P') {
   		system("CLS");
   		cout << "\n\n\n\n\n";
   		cout << "\t\t     Program is checking connectivity within the default graph. . .\n";
   		cout << "\n\t\t     " << system("PAUSE");
   		cout << "\n\n\n";
   		
   		if (graph.isStronglyConnected()) {
   			cout << "\t\t     This graph is strongly connected.\n";
   			cout << "\n\n";
   			graph.printGraph();
		}
		else {
			cout << "\t\t     This graph is not strongly connected.\n";
   			cout << "\n\n";
   			//cout << adding random edges
   			//function to add random edges
   			// cout << graph now is strongly connected
   			graph.printGraph();
		}
   }
   
   cout << "\n\n\n\n\n";
   cout << "\t\t     Enter P to proceed to the next step: ";
   cin >> proceed;
   
   // checking existing cycle
   if (proceed=='p' || proceed=='P') {
   		system("CLS");
   		cout << "\n\n\n\n\n";
   		cout << "\t\t     Program is checking whether the graph contains cycle. . .\n";
   		cout << "\n\t\t     " << system("PAUSE");
   		cout << "\n\n\n";
   		
   		if (graph.isCyclic()) {
   			cout << "\t\t     This graph contains cycle.\n";
   			cout << "\n\n";
   			graph.printGraph();
		}
		else {
			cout << "\t\t     This graph does not contain cycle.\n";
   			cout << "\n\n";
   			//cout << adding random edges
   			//function to add random
   			//cout << graph now finally contains cycle
   			graph.printGraph();
		}
   }
   
   cout << "\n\n\n\n\n";
   cout << "\t\t     Enter P to proceed to the next step: ";
   cin >> proceed;
   
   if (proceed=='p' || proceed=='P') {
   		system("CLS");
   		cout << "\n\n\n\n\n";
   		int src, dest;
	    cout<<"\t\t     Choose the first city as the source - 0, 1, 2, 3, or 4: ";
	    cin >> src;
	    cout << "\n\t\t     Choose the second city as the destination - 0, 1, 2, 3, or 4: ";
	    cin >> dest;
	    cout << "\n\n\n";
	    cout << "\t\t     Program is calculating the shortest path between " << src << " and " << dest << ". . .\n";
	    cout << "\n\t\t     " << system("PAUSE");
	    graph.shortestPath(src, dest);
   }
   
   return 0;
}
