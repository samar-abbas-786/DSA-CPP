#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> BFS(int n, vector<int> adj[])
{
    queue<int> q;
    vector<int> ans;
    vector<int> vis(n, 0);
    // Let starting Node is 0==> Zero Indexing
    vis[0] = 1;
    q.push(0);

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
    int n, m;
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    vector<vector<int>> adj(n + 1); // Using vector of vectors to store the adjacency list

    cout << "Enter the edges (pairs of connected vertices): " << endl;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // cout << "Adjacency list:" << endl;
    // for (int i = 1; i <= n; i++)
    // {
    //     cout << i << " -> ";
    //     for (int j = 0; j < adj[i].size(); j++)
    //     {
    //         cout << adj[i][j] << " ";
    //     }
    //     cout << endl;
    // }


        return 0;
}
