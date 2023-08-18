#include <iostream>
#include <vector>
#include <algorithm> 

class Owner
{
private:
    int m_x;
    int m_y;
    int m_z;

public:
    Owner(int x, int y, int z) : m_x(x), m_y(y), m_z(z) { }

    friend std::ostream& operator<<(std::ostream& out, const Owner& o)
    {
        return out << "Owner(" << o.m_x << ", " << o.m_y << ", " << o.m_z << ')';
    }
};

class Shape
{
public:
    virtual std::ostream& print(std::ostream& out) const = 0;

    friend std::ostream& operator<<(std::ostream& out, const Shape& s)
    {
        return s.print(out);
    }
    virtual ~Shape() = default;
};

class Triangle : public Shape
{
private:
    Owner m_p1;
    Owner m_p2;
    Owner m_p3;

public:
    explicit Triangle(const Owner& p1, const Owner& p2, const Owner& p3) : m_p1(p1), m_p2(p2), m_p3(p3)
    {
    }

    std::ostream& print(std::ostream& out) const override
    {
        out << "Triangle:\n";
        out << "  Point 1: " << m_p1 << '\n';
        out << "  Point 2: " << m_p2 << '\n';
        out << "  Point 3: " << m_p3;
        return out;
    }
};

class Circle : public Shape
{
private:
    Owner m_center;
    int m_radius;

public:
    explicit Circle(const Owner& center, int radius) : m_center(center), m_radius(radius)
    {
    }

    std::ostream& print(std::ostream& out) const override
    {
        out << "Circle:\n";
        out << "  Center: " << m_center << '\n';
        out << "  Radius: " << m_radius;
        return out;
    }
    int getRadius() const { return m_radius; }
};

int getLargestRadius(const std::vector<Shape*>& shapes)
{
    int largestRadius = 0;

    for (const auto* shape : shapes)
    {
        if (auto* circle = dynamic_cast<const Circle*>(shape))
        {
            largestRadius = std::max(largestRadius, circle->getRadius());
        }
    }

    return largestRadius;
}

int main()
{
    std::vector<Shape*> shapes;
    for (int i = 0; i < 2; ++i) {
        shapes.push_back(new Circle(Owner{ 1, 2, 3 }, 7));
        shapes.push_back(new Triangle(Owner{ 1, 2, 3 }, Owner{ 4, 5, 6 }, Owner{ 7, 8, 9 }));
    }

    for (const auto* shape : shapes)
        std::cout << *shape << '\n';

    std::cout << "The largest radius is: " << getLargestRadius(shapes) << '\n';

    for (const auto* shape : shapes)
        delete shape;

    return 0
