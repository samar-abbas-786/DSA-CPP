#include <iostream>
#include <vector>
#include <queue>
#include <climits> // For INT_MAX
using namespace std;

vector<int> Dijkstra(int v, vector<vector<pair<int, int>>> &adj, int s)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(v, INT_MAX); // Initialize distances with a large number

    dist[s] = 0;
    pq.push({0, s}); // Push the source node with distance 0

    while (!pq.empty())
    {
        int dis = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        // If the distance is greater than the already found shortest distance, skip
        if (dis > dist[node])
            continue;

        for (auto it : adj[node])
        {
            int adjNode = it.first;
            int edgeWeight = it.second;

            // If a shorter path to adjNode is found
            if (dis + edgeWeight < dist[adjNode])
            {
                dist[adjNode] = dis + edgeWeight;
                pq.push({dist[adjNode], adjNode});
            }
        }
    }
    return dist;
}

int main()
{
    int v, m; // Number of vertices and edges
    cout << "Enter the number of vertices: ";
    cin >> v;
    cout << "Enter the number of edges: ";
    cin >> m;

    vector<vector<pair<int, int>>> adj(v); // Adjacency list

    cout << "Enter each edge in the format 'u v w' where u and v are vertices and w is the weight:" << endl;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // For undirected graph, add edge in both directions
    }

    int s;
    cout << "Enter the Source Node (0 to " << v - 1 << "): ";
    cin >> s;

    // Input validation
    // if (s < 0 || s >= v)
    // {
    //     cout << "Invalid source node. Exiting." << endl;
    //     return 1;
    // }

    vector<int> distances = Dijkstra(v, adj, s);

    cout << "Distances from source " << s << ":\n";
    for (int i = 0; i < v; i++)
    {
        if (distances[i] == INT_MAX)
            cout << "Vertex " << i << ": INF" << endl;
        else
            cout << "Vertex " << i << ": " << distances[i] << endl;
    }
    return 0;
}
