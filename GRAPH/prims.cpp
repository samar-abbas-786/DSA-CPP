#include <iostream>
// #include <bits/stdc++.h>
#include <vector>
#include <queue>

using namespace std;

int SpanningTree(int V, vector<vector<pair<int, int>>> &adj)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> vis(V, 0);
    pq.push({0, 0});
    int sum = 0;
    while (!pq.empty())
    {
        auto it = pq.top();
        pq.pop();
        int node = it.second;
        int wt = it.first;
        if (vis[node] == 1)
        {
            continue;
        }
        vis[node] = 1;
        sum += wt;

        for (auto it : adj[node])
        {
            int adjNode = it.first;
            int adW = it.second;
            if (!vis[adjNode])
            {
                pq.push({adW, adjNode});
            }
        }
    }
    return sum;
};
int main()
{
    int V, E;
    cout << "Enter the No. of Node" << endl;
    cin >> V;
    cout << "Enter the No. of Edges" << endl;
    cin >> E;
    vector<vector<pair<int, int>>> adj(V);
    

    cout << "Enter the Pair for Adjacency List" << endl;
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    cout << "The Minimum Spanning Tree Sum is:" << SpanningTree(V, adj);

    return 0;
}