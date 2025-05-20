#include <iostream>
using namespace std;

struct Node
{
public:
    int data;
    struct Node *left;
    struct Node *right;

public:
    Node(int val)
    {
        data = val;
        left = right = NULL;
    }
};

int main()
{
    Node *root = new Node(1);
    root->left = new Node(2);
    root->left=new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);

    
    return 0;
}