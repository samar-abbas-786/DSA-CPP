#include <iostream>
using namespace std;
class student
{
public:
    virtual void samar()
    {
        cout << "Base " << endl;
    }
};

class child : public student
{
public:
    void samar()
    {
        cout << "Derived Class" << endl;
    }
};

int main()
{
    child obj;

    student *ptr;
    ptr = &obj;
    ptr->samar();

    return 0;
}