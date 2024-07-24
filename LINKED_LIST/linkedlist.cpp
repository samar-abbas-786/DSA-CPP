#include <iostream>
#include <vector>
using namespace std;
class Node
{
public:
    int data;
    Node *next;

    // Constructor
    Node(int data)
    {
        this->data = data;
        this->next = nullptr;
    }
};
// Convert Array to Linked List
Node *convertArray2LL(vector<int> &arr)
{
    Node *head = new Node(arr[0]);
    Node *mover = head;
    for (int i = 1; i < arr.size(); i++)
    {
        Node *temp = new Node(arr[i]);
        mover->next = temp;
        mover = temp;
    }
    return head;
}
Node *deleteHead(Node *head)
{
    Node *temp = head;
    head = head->next;
    free(temp);
    return head;
}
Node *print(Node *head)
{
    Node *temp = head;
    if (head->next == nullptr)
        return head;
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
}
Node *deleteTail(Node *head)
{
    Node *temp = head;
    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
}
int main()
{
    // Node *node1 = new Node(10);
    // cout << node1->data << endl;
    // cout << node1->next << endl;
    vector<int> arr = {2, 3, 4, 5, 32, 45};
    Node *head = convertArray2LL(arr);
    print(head);
    deleteTail(head);
    cout << endl;
    print(head);
    // Node *temp = head;
    // while (temp)
    // {
    //     cout << temp->data << "->";
    //     temp = temp->next;
    // }

    // Delete head

    return 0;
}