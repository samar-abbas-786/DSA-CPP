#include <iostream>
using namespace std;

class parent
{
public:
    void samar()
    {
        cout << "My Name is Base Samar" << endl;
    }
};
class Child : public parent
{

public:
    void samar()
    {
        cout << "My Name is Derived Samar" << endl;
        // parent::samar(); //"My Name is Base Samar"
    }
};

int main()
{
    Child obj;
    // obj.samar(); //  =>This will print Derived Samar

    // obj.parent::samar(); // parent ke andar ka samar() function run krega

    parent *ptr = &obj;
    ptr->samar(); //  =>This will print Base Samar

    return 0;
}