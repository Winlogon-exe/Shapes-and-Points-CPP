#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <algorithm>
class Owner
{
private:
    std::string name;
public:
    Owner(std::string name):name(name)
    {

    }
    friend std::ostream& operator<<(std::ostream& out, const Owner& owner)
    {
        return out << "Owner(" << owner.name << ")";
    }
};

class Shape
{
public:
    virtual double getArea() const = 0;
    virtual const Owner& getOwner() const = 0;
    virtual std::ostream& print(std::ostream& out) const = 0;
    virtual ~Shape() = default;

    friend std::ostream& operator<<(std::ostream& out, const Shape& p)
    {
        return p.print(out);
    }
};

class Rectangle : public Shape
{
private:
    double m_width;
    double m_height;
    Owner m_owner;

public:
    Rectangle(double width, double height, const Owner& owner) : m_width(width), m_height(height), m_owner(owner)
    {
    }

    double getArea() const override { return m_width * m_height; }

    const Owner& getOwner() const override { return m_owner; }

    std::ostream& print(std::ostream& out) const override
    {
        out << "Rectangle:\n";
        out << "  Width: " << m_width << '\n';
        out << "  Height: " << m_height << '\n';
        out << "  Owner: " << m_owner << '\n';
        out << "  Area: " << getArea();
        return out;
    }
};

class Square : public Shape
{
private:
    double m_side;
    Owner m_owner;

public:
    Square(double side, const Owner& owner) : m_side(side), m_owner(owner)
    {
    }

    double getArea() const override { return m_side * m_side; }

    const Owner& getOwner() const override { return m_owner; }

    std::ostream& print(std::ostream& out) const override
    {
        out << "Square:\n";
        out << "  Side: " << m_side << '\n';
        out << "  Owner: " << m_owner << '\n';
        out << "  Area: " << getArea();
        return out;
    }
};


void AddObject()
{
    std::string squareName = "alice";
    std::string rectangleName = "jhon";

    Owner owner1(squareName);
    Owner owner2(rectangleName);

    std::vector<Shape*> v = {
        new Rectangle(5,5,rectangleName),
        new Square(10,squareName)
    };

    for (const auto& element : v)
    {
        std::cout << *element <<"\n\n";
    }

    for (const auto* element : v)
        delete element;
}

int main()
{
    AddObject();
    return 0;
}
