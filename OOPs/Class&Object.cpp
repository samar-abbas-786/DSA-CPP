
#include <iostream>
using namespace std;

class student
{

public:
   string name;
   int roll_no;
   float cpi;
};

class fruit
{ public:
   string name;
   string color;
};

int main()
{
   student s1; // Object
   s1.name = "samar";
   s1.roll_no = 29;
   s1.cpi = 8.01;
   cout << s1.name << "-" << s1.roll_no << "-" << s1.cpi << endl;

   fruit *mango = new fruit(); //Creating Object Using Pointer
   mango->name = "mango";
   mango->color = "Green";
   cout<< mango->name << "-"<<mango->color<<endl;

   return 0;
}
