#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Owner
{
private:
    std::string name;

public:
   Owner(std::string&& name) noexcept : name(std::move(name)) { std::cout << "move"; };
   Owner(const std::string& name) : name(name) { std::cout << "copy"; }

    friend std::ostream& operator<<(std::ostream& out, const Owner& owner)
    {
        return out << "Owner(" << owner.name << ")";
    }

    Owner& operator=(const Owner& other) noexcept
    {
        if (this != &other)
            name = other.name;
        return *this;
    }
};

class Shape
{
public:
    virtual double getArea() const = 0;
    virtual const  Owner& getOwner() const = 0;
    virtual void printInfo() const = 0;
    virtual ~Shape() = default;
};

class Rectangle : public Shape
{
private:
    double m_width;
    double m_height;
    Owner m_owner; //Участки не могу существовать без владельца 

public:
    Rectangle(double width, double height, const Owner& owner) : m_width(width), m_height(height), m_owner(owner)
    {
    }

    double getArea() const override { return m_width * m_height;}

    const Owner& getOwner() const override { return m_owner; }


    void printInfo() const override
    {
        std::cout << "Rectangle:\n";
        std::cout << "  Width: " << m_width << '\n';
        std::cout << "  Height: " << m_height << '\n';
        std::cout << "  Owner: " << m_owner << '\n';
        std::cout << "  Area: " << getArea();
    }
};

class Square : public Shape 
{
private:
    double m_side;
    Owner m_owner;//Участки не могу существовать без владельца 

public:
    Square(double side, const Owner& owner) : m_side(side), m_owner(owner) 
    {
    }

    double getArea() const override { return m_side * m_side; }

    const Owner& getOwner() const override { return m_owner; }

    void printInfo() const override
    {
        std::cout << "Square:\n";
        std::cout << "  Side: " << m_side << '\n';
        std::cout << "  Owner: " << m_owner << '\n';
        std::cout << "  Area: " << getArea();
    }
};

void AddObject()
{
    std::vector<std::unique_ptr<Shape>> Shapes;
    std::string SquareName = "alice";
    std::string RectangleName = "jhon"; 

    Owner owner1(std::move(SquareName));
    Owner owner2(std::move(RectangleName)); 

    Shapes.push_back(std::make_unique<Square>(5, owner1));   //std::move?
    Shapes.push_back(std::make_unique<Rectangle>(4, 7, owner2));  //std::move?

    for (const auto& plot : Shapes)
    {
        plot->printInfo();
        std::cout << "\n\n";
    }
}

int main()
{
    AddObject();
    return 0;
}
