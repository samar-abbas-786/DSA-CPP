#include <iostream>
using namespace std;
class Node
{
public:
    int val;
    Node *next;

    Node(int data)
    {
        val = data;
        next = NULL;
    }
};
class LinkedList
{
public:
    Node *head;

    LinkedList()
    {
        head = NULL;
    }

    void insert(int value)
    {
        Node *new_node = new Node(value);
        if (head == NULL)
        {
            head = new_node;
            return;
        }
        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }

    void display()
    {

        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->val << "->";
            temp = temp->next;
        }
        cout << "NULL";
    }
};
void deleteAlternateNodes(Node *&head)
{
    Node *curr_Node = head;
    while (curr_Node != NULL && curr_Node->next != NULL)
    {
        Node *temp = curr_Node->next;
        curr_Node->next = curr_Node->next->next;
        free(temp);
        curr_Node = curr_Node->next;
    }
    cout << endl;
}
int main()
{
    LinkedList ll;
    ll.insert(1);
    ll.insert(2);
    ll.insert(3);
    ll.insert(4);
    ll.insert(5);
    ll.insert(6);
    ll.insert(7);
    ll.display();
    deleteAlternateNodes(ll.head);
    ll.display();

    return 0;
}