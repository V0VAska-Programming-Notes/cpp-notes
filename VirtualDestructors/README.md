При наследовании не следует забывать о виртуальных деструкторах.
Данный простенький пример имеет вид:

```c++
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
```

При выполнении программы мы получим в терминале:

```
Base::Base()
Derived::Derived()
Base::~Base()
```

То есть, ежели была выполнена какая-то инициализация в Derived, связанная с выделением памяти, например, то косячок - деструктор не был вызван.
Достаточно объявить в классе Base деструктор виртуальным,

```c++
    virtual ~Base()
    {
        std::cout << "Base::~Base()" << std::endl;
    }
```

то всё будет чики-пуки.
