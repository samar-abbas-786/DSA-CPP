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

void insertAtHead(Node *&head, int val)
{

    Node *new_node = new Node(val);
    new_node->next = head;
    head = new_node;
};

void insertAtEnd(Node *&head, int val)
{

    Node *new_node = new Node(val);
    Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    // temp has reached last node
    temp->next = new_node;
    new_node->next = NULL;
};

void insertAtPosition(Node *&head, int val, int k)
{
    if (k == 0)
    {
        insertAtHead(head, val);
        return;
    }

    Node *new_node = new Node(val);
    Node *temp = head;
    int curr_position = 0;
    while (curr_position != (k - 1))
    {
        temp = temp->next;
        curr_position++;
    }
    // temp is pointing to at node before position of insertion i.e: k-1

    new_node->next = temp->next;
    temp->next = new_node;
};

void updateAtPosition(Node *&head, int val, int k)
{
    Node *new_node = new Node(val);
    Node *temp = head;
    int curr_position = 0;
    while (curr_position != k)
    {
        temp = temp->next;
        curr_position++;
    }
    // reached at k
    temp->val = val;
}

void deleteAtHead(Node *&head)
{
    Node *temp = head;
    head = head->next;
    free(temp);
};

void deleteAtEnd(Node *&head)
{
    Node *Second_last = head;
    while (Second_last->next->next != NULL)
    {
        Second_last = Second_last->next;
    }
    Node *temp = Second_last->next;
    Second_last->next = NULL;
    free(temp);
}

void deleteAtPosition(Node *&head, int k)
{
    if (k == 0)
    {
        deleteAtHead(head);
        return;
    }
    Node *prev = head;
    int curr_position = 0;
    while (curr_position != k - 1)
    {
        prev = prev->next;
        curr_position++;
    }
    Node *temp = prev->next;
    prev->next = prev->next->next;
    free(temp);
}

void display(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->val << "->"
             << " ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

int main()
{

    Node *head = NULL;
    insertAtHead(head, 1);
    insertAtHead(head, 4);
    insertAtHead(head, 9);
    insertAtEnd(head, 999);
    display(head);
    insertAtHead(head, 10);
    insertAtPosition(head, 56, 2);
    display(head);
    updateAtPosition(head, 786, 1);
    display(head);
    deleteAtHead(head);
    display(head);
    deleteAtEnd(head);
    display(head);
    deleteAtPosition(head, 2);
    display(head);

    return 0;
}