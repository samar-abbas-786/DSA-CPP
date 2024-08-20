#include <iostream>
#include <vector>

using namespace std;

class MinHeap
{
    vector<pair<int, int>> heap;

    void heapifyUp(int index)
    {
        if (index == 0)
            return; // Root node, no parent to compare with

        int parentIndex = (index - 1) / 2;
        if (heap[parentIndex].first > heap[index].first)
        {
            swap(heap[parentIndex], heap[index]);
            heapifyUp(parentIndex);
        }
    }

    void heapifyDown(int index)
    {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < heap.size() && heap[leftChild].first < heap[smallest].first)
        {
            smallest = leftChild;
        }

        if (rightChild < heap.size() && heap[rightChild].first < heap[smallest].first)
        {
            smallest = rightChild;
        }

        if (smallest != index)
        {
            swap(heap[smallest], heap[index]);
            heapifyDown(smallest);
        }
    }

public:
    void push(pair<int, int> element)
    {
        heap.push_back(element);
        heapifyUp(heap.size() - 1);
    }

    void pop()
    {
        if (heap.empty())
            return;

        swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();
        heapifyDown(0);
    }

    pair<int, int> top()
    {
        if (heap.empty())
            throw runtime_error("Heap is empty!");

        return heap[0];
    }

    bool empty()
    {
        return heap.size() == 0;
    }
};

int SpanningTree(int V, vector<vector<pair<int, int>>> &adj)
{
    MinHeap pq;
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
}

void printAdjList(int V, const vector<vector<pair<int, int>>> &adj)
{
    for (int i = 0; i < V; i++)
    {
        cout << "Node " << i << ":";
        for (auto edge : adj[i])
        {
            cout << " -> (" << edge.first << ", " << edge.second << ")";
        }
        cout << endl;
    }
}

int main()
{
    int V, E;
    cout << "Enter the No. of Nodes" << endl;
    cin >> V;
    cout << "Enter the No. of Edges" << endl;
    cin >> E;
    vector<vector<pair<int, int>>> adj(V);

    cout << "Enter the edges with weights (u v w):" << endl;
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    printAdjList(V, adj);
    cout << "The Minimum Spanning Tree Sum is: " << SpanningTree(V, adj) << endl;

    return 0;
}
