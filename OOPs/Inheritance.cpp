
#include <iostream>
using namespace std;
class parent{
public:
int x;

protected:
int y;

private:
int z;

};

int main()
{
 class child1 : public parent{
   //x will become public 
   //y will become public
   //z will inaccesible 
 };
class child2 : protected parent{
   //x will become protected 
   //y will become protected
   //z will inaccesible 
};
class child3 : private parent{
   //x will become private 
   //y will become private
   //z will inaccesible 
};

   return 0;
}
