#include <iostream>

class Base
{
public:
    Base()
    {
        std::cout << "Base::Base()" << std::endl;
    }
    ~Base()
    {
        std::cout << "Base::~Base()" << std::endl;
    }
};

class Derived: public Base
{
public:
    Derived()
    {
        std::cout << "Derived::Derived()" << std::endl;
    }
    ~Derived()
    {
        std::cout << "Derived::~Derived()" << std::endl;
    }
};

int main(int argc, char *argv[])
{
    Base *ptr = new Derived{};
    delete ptr;
    return 0;
}
