#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// BFS function to traverse the graph
vector<int> BFS(int start, int n, vector<vector<int>> &adj)
{
    queue<int> q;
    vector<int> ans;
    vector<int> vis(n + 1, 0);  // `n + 1` to accommodate 1-based indexing

    // Start BFS from the specified node
    vis[start] = 1;
    q.push(start);

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        ans.push_back(node);

        for (auto it : adj[node])
        {
            if (!vis[it])
            {
                vis[it] = 1;
                q.push(it);
            }
        }
    }
    return ans;
}

int main()
{
    int n, m, start;
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);  // Using vector of vectors to store the adjacency list

    cout << "Enter the edges (pairs of connected vertices): " << endl;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout << "Enter the starting node for BFS: ";
    cin >> start;

    // Perform BFS from the specified starting node and get the traversal order
    vector<int> bfs_result = BFS(start, n, adj);

    // Print the BFS traversal
    cout << "BFS Traversal starting from node " << start << ":" << endl;
    for (int node : bfs_result)
    {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
