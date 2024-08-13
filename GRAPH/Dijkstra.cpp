
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<int> Dijkstra(int v, vector<vector<pair<int, int>>> &adj, int s)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(v);
    for (int i = 0; i < v; i++)
    {
        dist[i] = INT_MAX;
    }

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty())
    {
        int dis = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        for (auto it : adj[node])
        {
            int edgeWeight = it.second;
            int adjNode = it.first;

            if (dis + edgeWeight < dist[adjNode])
            {
                dist[adjNode] = dis + edgeWeight;
                pq.push({dist[adjNode], adjNode});
            }
        }
    }
    return dist;
}

//
int main()
{

    // Dijkstra
    int v = 5; // Number of vertices
    vector<vector<pair<int, int>>> adj(v);

    // Example graph with 5 vertices (0-indexed)
    adj[0].push_back({1, 10});
    adj[0].push_back({4, 3});
    adj[1].push_back({2, 2});
    adj[2].push_back({3, 9});
    adj[4].push_back({2, 1});
    adj[4].push_back({3, 2});

int s;
    cout << "Enter the Source Node" << endl;
    cin >> s;
     vector<int> distances = Dijkstra(v, adj, s);

    cout << "Distances from source " << s << ":\n";
    for (int i = 0; i < v; i++)
    {
        cout << "Vertex " << i << ": " << distances[i] << endl;
    }
    return 0;
}