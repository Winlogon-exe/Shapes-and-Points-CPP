#include <vector>
#include <iostream>
#include <algorithm> // для std::max

class Point
{
private:
    int m_x;
    int m_y;
    int m_z;

public:
    Point(int x, int y, int z)
        : m_x(x), m_y(y), m_z(z)
    {

    }

    friend std::ostream& operator<<(std::ostream& out, const Point& p)
    {
        return out << "Point(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ')';
    }
};

class Owner
{
private:
    std::string m_name;

public:
    Owner(std::string name) : m_name(name) {}

    friend std::ostream& operator<<(std::ostream& out, const Owner& owner)
    {
        return out << "Owner: " << owner.m_name;
    }
};

class Shape
{
public:
    virtual std::ostream& print(std::ostream& out) const = 0;

    friend std::ostream& operator<<(std::ostream& out, const Shape& p)
    {
        return p.print(out);
    }
    virtual ~Shape() = default;
};

class Triangle : public Shape
{
private:
    Point m_p1;
    Point m_p2;
    Point m_p3;
    Owner m_owner;

public:
    Triangle(const Point& p1, const Point& p2, const Point& p3, const Owner& owner)
        : m_p1(p1), m_p2(p2), m_p3(p3), m_owner(owner)
    {
    }

    std::ostream& print(std::ostream& out) const override
    {
        out << "Triangle(" << m_p1 << ", " << m_p2 << ", " << m_p3 << ")\n";
        out << "  " << m_owner;
        return out;
    }
};

class Circle : public Shape
{
private:
    Point m_center;
    int m_radius = 0;
    Owner m_owner;

public:
    Circle(const Point& center, int radius, const Owner& owner)
        : m_center(center), m_radius(radius), m_owner(owner)
    {
    }

    std::ostream& print(std::ostream& out) const override
    {
        out << "Circle(" << m_center << ", radius " << m_radius << ")\n";
        out << "  " << m_owner;
        return out;
    }

    int getRadius() const { return m_radius; }
};

int getSum(const std::vector<Shape*>& v)
{
    int sum = 0;

    return sum;
}

int main()
{
    std::vector<Shape*> v{
        new Circle{ Point{1, 2, 3}, 7, Owner("alice") },
        new Triangle{ Point{1, 2, 3}, Point{4, 5, 6}, Point{7, 8, 9}, Owner("bob") },
        new Circle{ Point{4, 5, 6}, 3, Owner("john") }
    };

    for (const auto* element : v) // элемент будет Shape*
        std::cout << *element << '\n';

    std::cout << "The largest radius is: " << getSum(v) << '\n';

    for (const auto* element : v)
        delete element;

    return 0;
}
