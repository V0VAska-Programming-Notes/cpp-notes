#include <iostream>

class Base
{
public:
    int *ptr;
    Base(int i): ptr{new int(i)}{}
    Base(const Base&);
    Base& operator=(const Base& baseObj)
    {
        // not a self-assignment
        if(this != &baseObj)
        {
            delete this->ptr;
            this->ptr = new int{*(baseObj.ptr)};
        }
        return *this;
    }

    ~Base();
};

Base::Base(const Base& baseObj) : ptr{nullptr}
{
    this->ptr = new int{*(baseObj.ptr)};
}

Base::~Base()
{
    if (ptr != nullptr)
    {
        // do not forget to free resources
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
    // copy constructor
    someFunc(objBase);

    // copy constructor
    //Base objBase1 = objBase;
    
    Base objBase1{20};
    // copy assignment
    objBase1 = objBase;
    return 0;
}
