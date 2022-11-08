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

void someFunc(Base param)
{
    std::cout << "Doing something: " << *(param.ptr) << std::endl;
}

int main(int argc, char *argv[])
{
    Base objBase{10};
    someFunc(objBase);
    std::cout << "LOL..." << std::endl;
    return 0;
}
