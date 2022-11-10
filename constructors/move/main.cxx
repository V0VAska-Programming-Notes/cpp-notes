#include <iostream>

class Base
{
public:
    int *ptr;
    Base(int i): ptr{new int(i)}{}
    Base(const Base&) = delete;
    Base(Base&&);
    Base& operator=(const Base&) = delete;
    Base& operator=(Base&& objBase)
    {
        if (this != &objBase)
        {
            // free resources
            delete ptr;

            ptr = objBase.ptr;

            objBase.ptr = nullptr;
        }
        return *this;
    }
    ~Base();
};

Base::Base(Base&& baseObj) : ptr{nullptr}
{
    this->ptr = baseObj.ptr;

    // do not forget to do this
    baseObj.ptr = nullptr;
}

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
    Base objBase{10};
    Base objBase1{std::move(objBase)};
    std::cout << "*(objBase1.ptr) = " << *(objBase1.ptr) << std::endl;
    objBase = std::move(objBase1);
    std::cout << "*(objBase.ptr) = " << *(objBase.ptr) << std::endl;
    return 0;
}
