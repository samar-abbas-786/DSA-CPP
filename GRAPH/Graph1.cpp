#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

class graph
{
public:
    unordered_map<int, list<int>> adj;

    void addEdge(int u, int v, bool direction)
    {
        // bool-0==>undircted
        // bool-1==>dircted
    }
};

int main()
{

    return 0;
}