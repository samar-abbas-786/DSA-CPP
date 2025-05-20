#include <iostream>
#include <vector>
using namespace std;

int main()
{
    cout << "Enter the number of vertices and number of edges" << endl;
    int n, m;
    cin >> n >> m;
    vector<int> adj[n + 1];
    for (int i = 0; i < m; i++)
    {

        int v, u;
        cout << "Enter the node to connect";
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout << "Adjacency list are :";
    cout << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << i << ":";
        for (int neighbour : adj[i])
        {
            cout << neighbour + " ";
        }
    }

    return 0;
}