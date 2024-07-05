#include <iostream>
#include <iostream>
using namespace std;
class Node
{
public:
    int data;
    Node *next;

public:
    Node(int data1, Node *next1)
    {
        data = data1;
        next = nullptr;
    }

public:
    Node(int data1)
    {
        data = data1;
        next = nullptr;
    }
};
int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    Node *new_node = new Node(arr[1]);
    cout << new_node->data;
    return 0;
}
