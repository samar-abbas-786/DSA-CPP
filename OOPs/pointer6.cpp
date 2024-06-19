class Base
{
public:
    void func1();
    void func2();
    void func3();
}; // Base class with 3 functions created
class Child : public Base
{ // Class child inheriting from Base publicly
public:
    void func4(); // Child class also has 2 additional functions along with 3 of class Base
    void func5();
};
int main()
{
    // We have our main function where we create object of class base as b/
    Base b;
    b.func1();
    b.func2();
    b.func3(); // Pretty obvious as object of base class can call functions of Base

    Child c; // Object of class Derived created which calls functions of Base and Child class both
    c.func1();
    c.func2();
    c.func3();
    c.func4();
    c.func5();
    Base *ptr = &c;
    // So far so good, pretty intuitive things done, now we take base class pointer p
    Base *p;         // To this pointer we assign an object of child class
    p = new Child(); // It is possible for base class pointer to point to derived class object
    // Now we can call the functions of the class to which we made the pointer initially i.e. Base
    p->func1();
    p->func2();
    p->func3(); // We can call all functions of class Base, to which we made Base *p;
    // As pointer is of one class and object is of another class which inherits class one.
    // Functions of the class of which pointer is will be called.
    // p->fun4; // Can't be done as pointer is of base class and all functions of base class only will be called. Even if object is of derived class, functions of derived class cannot be called.
}
