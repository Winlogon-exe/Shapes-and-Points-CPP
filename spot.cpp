#include <iostream>

class Spot {
protected:
    double width;
    double height;

public:
    Spot(double w, double h) : width(w), height(h) {}

    virtual double CalculateArea() const = 0;
};

class Square : public Spot {
public:
    Square(double side) : Spot(side, side) {}

    double CalculateArea() const override  {
        return width * height; // Площадь квадрата: сторона * сторона
    }
};

class Triangle : public Spot {
public:
    Triangle(double base, double h) : Spot(base, h) {}

    double CalculateArea() const override  { 
        return  (width * height)/2; // Площадь треугольника: (основание * высота) / 2
    }
};

int main() {
    setlocale(LC_ALL, "RUS");
    Square square(5.0);
    Triangle triangle(4.0, 3.0);

    std::cout << "Площадь квадрата: " << square.CalculateArea() << " кв. ед." << std::endl;
    std::cout << "Площадь треугольника: " << triangle.CalculateArea() << " кв. ед." << std::endl;

    return 0;
}
