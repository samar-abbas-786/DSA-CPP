#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> DFS(int start, int n, vector<vector<int>> &adj)
{

    stack<int> st;
    vector<int> ans;
    vector<int> vis(n + 1, 0);
    vis[start] = 1;
    st.push(start);
    while (!st.empty())
    {
        int node = st.top();
        st.pop();
        ans.push_back(node);
        for (int neighbour : adj[node])
        {
            if (vis[neighbour] != 1)
            {
                vis[neighbour] = 1;

                st.push(neighbour);
            }
        }
    }
    return ans;
}

int main()
{
    int n, m;
    vector<vector<int>> adj(n + 1);
    cout << "Enter the Number of vertices and edges" << endl;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int start;
    cout << "Enter the starting node" << endl;
    cin >> start;

    vector<int> ans = DFS(start, n, adj);
    cout << "DFS is : ->";
    for (int node : ans)
    {
        cout << node << "-";
    }
    cout << endl;
    return 0;
}