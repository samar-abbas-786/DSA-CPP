#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> BFS(int starting_node, vector<int> list[], int n, int m)
{
    vector<int> vis(n + 1, 0);
    vector<int> ans;
    queue<int> q;
    q.push(starting_node);
    vis[starting_node] = 1;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        ans.push_back(node);

        for (auto it : list[node])
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
    cin >> n >> m;
    vector<int> list[n + 1];

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        list[u].push_back(v);
        list[v].push_back(u);
    }

    int starting_node = 1;

    vector<int> result = BFS(starting_node, list, n, m);
    
    for (int node : result)
    {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
