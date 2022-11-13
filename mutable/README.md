# Mutable.

Стартуем:

```c++
#include <vector>

class Vertex
{
public:
    int x, y;
};

double calculateArea(std::vector<Vertex> vertices = {})
{
    double result = 0;
    // tooooo long calculations
    return result;
}

class Polygon
{
    std::vector<Vertex> vertices;
public:
    Polygon(std::vector<Vertex> vxs = {})
        : vertices{ std::move(vxs) }
    {}

    double area() const
    {
        return calculateArea(vertices);
    }

    void add(const Vertex& vertex)
    {
        vertices.push_back(vertex);
    }
};

int main()
{
    Polygon polygon1;
    // etc.
    return 0;
}
```

Функция calculateArea() достаточно ресурсоёмкая, чтобы вызывать её каждый раз. Напрашивается такое решение:

```c++
class Polygon
{
    std::vector<Vertex> vertices;
    double cachedArea { 0 };
public:
    Polygon(std::vector<Vertex> vxs = {})
        : vertices{ std::move(vxs) }
    {}

    double area() const
    {
        if (cachedArea == 0)
        {
            cachedArea = calculateArea(vertices);
        }
        return cachedArea;
    }

    void add(const Vertex& vertex)
    {
        vertices.push_back(vertex);
        cachedArea = 0;
    }
};
```

Но геттер area() резонно объявлен const - компилятор будет жаловаться на изменение cachedArea. По этой же причине невозможно впихнуть и мутексы, ежели задуматься о потокобезопасности.

Для таких случаев и предусмотрен спецификатор mutable, позволяющий изменять значение данного члена класса даже если содержащий его объект объявлен const.

```c++
#include <vector>

class Vertex
{
public:
    int x, y;
};

double calculateArea(std::vector<Vertex> vertices = {})
{
    double result = 0;
    // tooooo long calculations
    return result;
}

class Polygon
{
    std::vector<Vertex> vertices;
    mutable double cachedArea { 0 };
public:
    Polygon(std::vector<Vertex> vxs = {})
        : vertices{ std::move(vxs) }
    {}

    double area() const
    {
        if (cachedArea == 0)
        {
            cachedArea = calculateArea(vertices);
        }
        return cachedArea;
    }

    void add(const Vertex& vertex)
    {
        vertices.push_back(vertex);
        cachedArea = 0;
    }
};

int main()
{
    Polygon polygon1;
    // etc.
    return 0;
}
```
