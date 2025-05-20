#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

void displayResidualGraph(vector<vector<int>> &residualGraph)
{
    cout << "\nResidual Graph:" << endl;
    for (int i = 0; i < residualGraph.size(); i++)
    {
        for (int j = 0; j < residualGraph[i].size(); j++)
        {
            cout << residualGraph[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool bfs(vector<vector<int>> &residualGraph, int source, int sink, vector<int> &parent)
{
    int n = residualGraph.size();
    vector<bool> visited(n, false);
    queue<int> q;

    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; v++)
        {
            if (!visited[v] && residualGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;

                if (v == sink)
                    return true;
            }
        }
    }
    return false;
}

int fordFulkerson(vector<vector<int>> &graph, int source, int sink)
{
    int u, v;
    int n = graph.size();

    vector<vector<int>> residualGraph = graph;

    vector<int> parent(n);

    int maxFlow = 0;

    while (bfs(residualGraph, source, sink, parent))
    {
        int pathFlow = INT_MAX;
        for (v = sink; v != source; v = parent[v])
        {
            u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        for (v = sink; v != source; v = parent[v])
        {
            u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        cout << "Path Flow: " << pathFlow << endl;
        displayResidualGraph(residualGraph);

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main()
{
    int n, m;
    cout << "Enter the number of nodes: ";
    cin >> n;

    cout << "Enter the number of edges: ";
    cin >> m;

    vector<vector<int>> graph(n, vector<int>(n, 0));

    cout << "Enter the edges and their capacities (u v capacity):\n";
    for (int i = 0; i < m; i++)
    {
        int u, v, capacity;
        cin >> u >> v >> capacity;
        graph[u][v] = capacity;
    }

    int source, sink;
    cout << "Enter the source node: ";
    cin >> source;

    cout << "Enter the sink node: ";
    cin >> sink;

    cout << "\nInitial Graph:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    int maxFlow = fordFulkerson(graph, source, sink);

    cout << "\nThe maximum possible flow is: " << maxFlow << endl;

    return 0;
}
