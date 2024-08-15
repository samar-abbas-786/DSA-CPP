#include <bits/stdc++.h>
using namespace std;

const int inf = 1e7; // Define infinity

int main()
{
    // n=no.of vertices
    // m = no. of edges
    int n, m;
    cout << "Enter the no. of vertex : ";
    cin >> n;
    cout << "Enter the no. of Edge : ";
    cin >> m;
    // Initialize distanceance vector with 'infinity'
    vector<int> distance(n + 1, inf);

    // Adjacency list to store the graph
    vector<vector<pair<int, int>>> graph(n + 1);
    cout << "Enter the edges (u v w):\n";
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w}); // Add edge from u to v with weight w
        graph[v].push_back({u, w}); // Since the graph is undirected, also add edge from v to u
    }
    int source;
    cout << "Enter the source vertex: ";
    cin >> source;
    distance[source] = 0; // distanceance to the source vertex is 0

    // set of pairs (distanceance, vertex)
    set<pair<int, int>> s;
    // {wt , vertex}
    s.insert({0, source}); // Insert the source vertex with distanceance 0

    while (!s.empty())
    {
        // Extract the vertex with the minimum distanceance
        auto x = *(s.begin());
        s.erase(x);

        // Iterate over all adjacent vertices (neighbors) of u
        for (auto it : graph[x.second])
        { // it is child or neighbour
            // If a shorter path to vertex v is found
            if (distance[it.first] > distance[x.second] + it.second)
            {
                s.erase({distance[it.first], it.first});
                distance[it.first] = distance[x.second] + it.second;
                // {wt , vertex}
                s.insert({distance[it.first], it.first});
            }
        }
    }

    cout << "Vertex and distanceance from Source:\n";
    // Output the shortest distanceances from the source vertex
    for (int i = 1; i <= n; i++)
    {
        if (distance[i] < inf)
        {
            cout << "Vertex " << i << ": " << distance[i] << "\n"; // Print distanceance if reachable
        }
        else
        {
            cout << "Vertex " << i << ": Infinity\n"; // Print -1 if not reachable
        }
    }

    return 0;
}