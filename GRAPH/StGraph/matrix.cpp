#include <iostream>
using namespace std;

int main()
{

    int n, m;
    cout << "Enter the number of nodes ans edges" << endl;
    cin >> n >> m;
    int adj[n + 1][m + 1];
    cout << "Enter the pair of " << m << " edges" << endl;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u][v] == 1;
        adj[v][u] == 1;
    }

    return 0;
}