#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;

int spanningTree(int V, vector<vector<int>> adj[])
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> vis(V, 0);
    vector<tuple<int, int, int>> mstEdges;

    int sum = 0;
    //{wt,node}
    pq.push({0, 0});
    while (!pq.empty())
    {
        auto it = pq.top();
        pq.pop();
        int wt = it.first;
        int node = it.second;

        if (vis[node] == 1)
        {
            continue;
        }

        vis[node] = 1;
        sum += wt;
        if (wt != 0)
        {
            for (auto adjNode : adj[node])
            {
                int nextNode = adjNode[0];
                int edgeWeight = adjNode[1];

                if (nextNode == node || vis[nextNode] == 1)
                {
                    continue;
                }
                mstEdges.push_back({nextNode, node, edgeWeight});
            }
        }
        for (auto it : adj[node])
        {
            int adjNode = it[0];
            int adjWeight = it[1];
            if (!vis[adjNode])
            {
                pq.push({adjWeight, adjNode});
            }
        }
    }
    cout << "Edges in the MST (Node1 - Node2, Weight):\n";
    for (auto edge : mstEdges)
    {
        int node1, node2, weight;
        tie(node1, node2, weight) = edge; // Decompose the tuple
        cout << "Node " << node1 << " - Node " << node2 << ", Weight: " << weight << endl;
    }
    return sum;
};

int main()
{
    int V = 5;
    vector<vector<int>> adj[V];

    // Example edges
    adj[0].push_back({1, 2});
    adj[1].push_back({0, 2});

    adj[1].push_back({2, 3});
    adj[2].push_back({1, 3});

    adj[0].push_back({3, 6});
    adj[3].push_back({0, 6});

    adj[1].push_back({3, 8});
    adj[3].push_back({1, 8});

    adj[1].push_back({4, 5});
    adj[4].push_back({1, 5});

    adj[2].push_back({4, 7});
    adj[4].push_back({2, 7});

    cout << "Total weight of MST: " << spanningTree(V, adj) << endl;

    return 0;
}
