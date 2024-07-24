#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node *back;

public:
    Node(int data1, Node *next1, Node *back1)
    {
        data = data1;
        next = next1;
        back = back1;
    }

public:
    Node(int data1)
    {
        data = data1;
        next = nullptr;
        back = nullptr;
    }
    static Node *convertArray2DDLL(vector<int> &arr)
    {
        Node *head = new Node(arr[0]);
        Node *prev = head;
        for (int i = 1; i < arr.size(); i++)
        {
            Node *temp = new Node(arr[i], nullptr, prev);
            prev->next = temp;
            prev = temp;
        }
        return head;
    }
    static void print(Node *head)
    {
        while (head != nullptr)
        {
            cout << head->data << " ";
            head = head->next;
        }
    }
};
int main()
{
    vector<int> arr = {1, 4, 6, 8, 9};
    Node *head = Node::convertArray2DDLL(arr);
    Node::print(head);
    return 0;
}