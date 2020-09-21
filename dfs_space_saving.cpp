// An Iterative C++ program to do DFS traversal from 
// a given source vertex. DFS(int s) traverses vertices 
// reachable from s. 
#include <bits/stdc++.h>
using namespace std; 

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const
    {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};
  
// This class represents a directed graph using adjacency 
// list representation 
class Graph 
{ 
    int V;    // No. of vertices 
    vector<int> *adj;    // adjacency arrays 
    unordered_map< pair<int, int>, int, pair_hash> edge_idx_map;

public:
    Graph(int V);  // Constructor
    int deg(int v); // return degree of vertex v 
    void addEdge(int v, int w); // to add an edge to graph
    void DFS();  // prints all vertices in DFS manner 
  
    // prints all not yet visited vertices reachable from s 
    void DFSUtil(int s, vector<bool> &visited); 
}; 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new vector<int>[V];
} 

int Graph::deg(int v)
{
    return adj[v].size();
}
  
void Graph::addEdge(int v, int w) 
{ 
    adj[v].push_back(w); // Add w to v’s list.
    edge_idx_map[{v, w}] = adj[v].size() - 1;
    adj[w].push_back(v); // Add w to v’s list.
    edge_idx_map[{w, v}] = adj[w].size() - 1;  
}


// prints all not yet visited vertices reachable from v in undirected graph
void Graph::DFSUtil(int v, vector<bool> &visited) 
{ 
    // Create a stack for DFS 
    stack<int> stack;
    int k = -1, l = -1;
    int w, u;
  
    visited[v] = true;
    printf("%d ", v);
    while (true) {
        l++;
        if (l < deg(v)) {
            w = adj[v][(k + l + 1) % deg(v)];
            if (!visited[w]) {
                stack.push(l);
                k = edge_idx_map[{w, v}];
                l = -1;
                v = w;
                visited[v] = true;
                printf("%d ", v);
            }
        } else {
            if (stack.empty())
                break;
            u = adj[v][k];
            l = stack.top();
            stack.pop();
            k = (edge_idx_map[{u, v}] - (l + 1)) % deg(u);
            v = u;
        }
    }
}
  
// prints all vertices in DFS manner 
void Graph::DFS() 
{ 
    // Mark all the vertices as not visited 
    vector<bool> visited(V, false); 
  
    for (int i = 0; i < V; i++) 
        if (!visited[i]) 
            DFSUtil(i, visited); 
} 
  
// Driver program to test methods of graph class 
int main() 
{ 
    Graph g(5);  // Total 5 vertices in graph 
    g.addEdge(1, 0);
    g.addEdge(0, 2); 
    g.addEdge(2, 1);
    g.addEdge(0, 3);  
    g.addEdge(1, 4); 
  
    cout << "Following is Depth First Traversal\n"; 
    g.DFS();
    cout << endl; 
  
    return 0; 
} 
