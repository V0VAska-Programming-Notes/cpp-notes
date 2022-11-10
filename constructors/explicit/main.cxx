#include <iostream>

class Base
{
public:
    int *ptr;
    Base(int i): ptr{new int(i)}{}
    ~Base();
};

Base::~Base()
{
    if (ptr != nullptr)
    {
        delete ptr;
        ptr = nullptr;
    }
}

int main(int argc, char *argv[])
{
    Base objBase = 10;
    Base objBase1 = 20.0;
    return 0;
}
