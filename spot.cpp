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
        return out << "(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ')';
    }

    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getZ() const { return m_z; }
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
    virtual int getPointSum() const = 0;
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

    int getPointSum() const override
    {
        return m_p1.getX() + m_p1.getY() + m_p1.getZ() +
            m_p2.getX() + m_p2.getY() + m_p2.getZ() +
            m_p3.getX() + m_p3.getY() + m_p3.getZ();
    }

    std::ostream& print(std::ostream& out) const override
    {
        out << "Triangle " << m_owner << "\n";
        out << "  Points: " << m_p1 << ", " << m_p2 << ", " << m_p3 << '\n';
        return out;
    }
};

class Circle : public Shape
{
private:
    Point m_center;
    Owner m_owner; 
    int m_radius = 0;

public:
    Circle(const Point& center, int radius, const Owner& owner)
        : m_center(center), m_radius(radius), m_owner(owner)
    {
    }

    int getPointSum() const override
    {
        return m_center.getX() + m_center.getY() + m_center.getZ();
    }

    std::ostream& print(std::ostream& out) const override
    {
        out << "Circle " << m_owner << "\n";
        out << "  Center: " << m_center << ", Radius: " << m_radius << '\n';
        return out;
    }
};

int getSum(const std::vector<Shape*>& v)
{
    int sum = 0;
    for (const auto* element : v)
    {
        sum += element->getPointSum();
    }
    return sum;
}

int main()
{
    std::vector<Shape*> v{
        new Circle{ Point{1, 2, 3}, 7, Owner("alice") },
        new Triangle{ Point{1, 2, 3}, Point{4, 5, 6}, Point{7, 8, 9}, Owner("bob") },
        new Circle{ Point{4, 5, 6}, 3, Owner("john") }
    };

    for (const Shape* element : v) 
        std::cout << *element << '\n';

    std::cout << "The sum of all points is: " << getSum(v) << '\n';

    for (const auto* element : v)
        delete element;

    return 0;
}
