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
