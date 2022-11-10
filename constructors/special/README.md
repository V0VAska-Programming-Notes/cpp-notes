# Implicit members

The six special members functions described above are members implicitly declared on classes under certain circumstances:

| Member function | implicity defined | default definition |
| --- | --- | --- |
| default constructor | if no other constructors | does nothing |
| destructor | if no destructor | 	does nothing |
| copy constructor | if no move constructor and no move assignment | copies all members |
| copy assignment | if no move constructor and no move assignment | copies all members |
| move constructor | if no destructor, no copy constructor and no copy nor move assignment | moves all members |
| move assignment | if no destructor, no copy constructor and no copy nor move assignment | moves all members |

Notice how not all `special member` functions are implicitly defined in the same cases. This is mostly due to backwards compatibility with C structures and earlier C++ versions, and in fact some include deprecated cases.
Fortunately, each class can select explicitly which of these members exist with their default definition or which are deleted by using the keywords `default` and `delete`, respectively.
The syntax is either one of:

```c++
function_declaration = default;
function_declaration = delete;
```

При работе с динамически выделяемой памятью следует явно определять `copy` и `move` конструкторы и присваивания (если они нужны). Иначе следует их запрещать.

# Default constructor

Позволяет создать экземпляр объекта класса самым простецким способом:

```c++
class SomeClass
{
	...
};

SomeClass someObject;
```

Как правило, хоть один конструктор существует и явно определён программистом, так что дефолтный компилятором не генерится согласно табличке выше. Но если по каким-то причинам этот конструктор необходим, то следует его "задефолтить":

```c++
class SomeClass
{
	SomeClass() = default;
};
```

Неясно только зачем, поскольку он вообще никак не инициализирует - просто будет выделена память под объект и все данные будут "от балды".

