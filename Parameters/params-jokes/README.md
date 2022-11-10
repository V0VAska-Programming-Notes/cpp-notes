# Мелкий косячок-с, а неприятно.

Примерчик реальный, только в упрощённой форме. Был у мну до-о-о-олгий перерыв в кодировании на C++ и вот как-то нужда прибила...
Радостно стал пальцами по клаве шлёпать, опираясь по памяти на знания из ископаемых времён.

<details><summary>main.cxx</summary>

```c++
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
```

</details>

Как лечить и избегать, а по возможности и использовать move и copy - позже допишу (возможно).

# Решился-таки дописать...

## Причина

Ошибочка примитивная - как параметр был создан новый экземпляр класса и все члены были тупо скопированы. И скопировался-то указатель, а не область памяти, га которую ссылается указатель.

## Простейшее лекарство.

Достаточно передать параметр не по значению, а по ссылке:

```c++
void someFunc(Base& param)
```

## Как обезопаситься от подобных ляпов.

Заглянем сюда - [special member functions](../../constructors/special).
