#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Owner
{
private:
    std::string name;

public:
    Owner(std::string name) : name(name) { }

    friend std::ostream& operator<<(std::ostream& out, const Owner& o)
    {
        return out << "Owner(" << o.name << ")";
    }
};

class Shape
{
public:
    virtual double getArea() const = 0;
    virtual Owner getOwner() const = 0;
    virtual void printInfo(std::ostream& out) const = 0;
    virtual ~Shape() = default;
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

    double getArea() const override
    {
        return m_width * m_height;
    }

    Owner getOwner() const override
    {
        return m_owner;
    }

    void printInfo(std::ostream& out) const override
    {
        out << "Rectangle:\n";
        out << "  Width: " << m_width << '\n';
        out << "  Height: " << m_height << '\n';
        out << "  Owner: " << m_owner << '\n';
        out << "  Area: " << getArea();
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

    double getArea() const override { return m_side * m_side;}

    Owner getOwner() const override {return m_owner;}

    void printInfo(std::ostream& out) const override
    {
        out << "Square:\n";
        out << "  Side: " << m_side << '\n';
        out << "  Owner: " << m_owner << '\n';
        out << "  Area: " << getArea();
    }
};

int main()
{
    std::vector<Shape*> Shapes;
    Owner owner1("John");
    Owner owner2("Alice");

    for (int i = 0; i < 1; ++i)
    {
        Shapes.push_back(new Square(5, owner1));
        Shapes.push_back(new Rectangle(4, 7, owner2));
    }

    for (const auto* plot : Shapes)
    {
        plot->printInfo(std::cout); 
        std::cout << "\n\n";
    }

    for (const auto* plot : Shapes)
        delete plot;

    return 0;
}
