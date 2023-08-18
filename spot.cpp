#include <iostream>
#include <vector>
#include <algorithm> 

class Point
{
private:
    int m_x;
    int m_y;
    int m_z;

public:
    Point(int x, int y, int z) : m_x(x), m_y(y), m_z(z) { }

    friend std::ostream& operator<<(std::ostream& out, const Point& p)
    {
        return out << "Point(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ')';
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
    Point p1;
    Point p2;
    Point p3;

public:
    explicit Triangle(const Point& p1, const Point& p2, const Point& p3) : p1(p1), p2(p2), p3(p3)
    {
    }

    std::ostream& print(std::ostream& out) const override
    {
        out << "Triangle:\n";
        out << "  Point 1: " << p1 << '\n';
        out << "  Point 2: " << p2 << '\n';
        out << "  Point 3: " << p3;
        return out;
    }
};

class Circle : public Shape
{
private:
    Point m_center;
    int m_radius;

public:
    explicit Circle(const Point& center, int radius) : m_center(center), m_radius(radius)
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
        shapes.push_back(new Circle(Point{ 1, 2, 3 }, 7));
        shapes.push_back(new Triangle(Point{ 1, 2, 3 }, Point{ 4, 5, 6 }, Point{ 7, 8, 9 }));
    }

    for (const auto* shape : shapes)
        std::cout << *shape << '\n';

    std::cout << "\nThe largest radius is: " << getLargestRadius(shapes) << '\n';

    for (const auto* shape : shapes)
        delete shape;

    return 0;
}
