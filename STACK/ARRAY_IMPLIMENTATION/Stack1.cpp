#include <iostream>
using namespace std;

class Stack
{
    int capacity;
    int *arr;
    int top;

public:
    Stack(int c)
    {
        this->capacity = c;
        arr = new int[c];
        top = -1; // Fix: Remove the int declaration to properly initialize the member variable.
    }

    void push(int data)
    {
        if (this->top == this->capacity - 1)
        {
            cout << "OVERFLOW\n"; // Fix: Correct the error message.
            return;
        }
        this->top++;
        this->arr[this->top] = data; // Fix: Correct the assignment operator.
    }

    int pop()
    {
        if (this->top == -1)
        {
            cout << "UNDERFLOW\n";
            return -404;
        }
        int poppedElement = this->arr[this->top];
        this->top--;
        return poppedElement; // Fix: Return the popped element.
    }

    int getTop()
    {
        if (this->top == -1)
        {
            cout << "NO-ELEMENT\n";
            return -404;
        }
        return this->arr[this->top];
    }

    bool isEmpty()
    {
        return this->top == -1;
    }

    bool isFull()
    {
        return this->top == this->capacity - 1;
    }

    int size()
    {
        return this->top + 1;
    }
};

int main()
{
    Stack s1(5);
    for (int i = 0; i < 5; i++)
    {
        s1.push(10);
    }
    cout << s1.getTop() << endl; // Fix: Add endl to flush the output buffer.

    s1.pop(); // Fix: Pop the element to avoid memory leaks.

    return 0;
}
