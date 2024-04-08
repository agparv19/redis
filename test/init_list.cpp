#include <iostream>
#include <initializer_list>
#include <vector>

// Base class Fancy
class Fancy {
public:
    virtual ~Fancy() {} // Make sure to have a virtual destructor for polymorphism
    virtual int getValue() const = 0; // Pure virtual function
};

// Derived class FancyObject_1
class FancyObject_1 : public Fancy {
public:
    FancyObject_1(int value) : value(value) {}
    int getValue() const override { return value; }
private:
    int value;
};

// Derived class FancyObject_2
class FancyObject_2 : public Fancy {
public:
    FancyObject_2(double value) : value(value) {}
    int getValue() const override { return static_cast<int>(value); } // Convert double to int
private:
    double value;
};

// Class that accepts an initializer list of Fancy objects in its constructor
class MyClass {
public:
    template<typename T>
    MyClass(std::initializer_list<T> list) {
        for (const auto& obj : list) {
            fancyObjects.push_back(obj);
        }
    }

    // Example member function to demonstrate usage
    void printValues() {
        for (const auto& obj : fancyObjects) {
            std::cout << obj->getValue() << " ";
        }
        std::cout << std::endl;
    }
private:
    std::vector<Fancy*> fancyObjects;
};

int main() {
    // Creating an instance of MyClass with an initializer list containing objects of different types
    MyClass<Fancy*> myObj({FancyObject_1(1), FancyObject_2(2.5), FancyObject_1(3), FancyObject_2(4.8)});

    // Calling a member function to print values
    myObj.printValues(); // Output: 1 2 3 4

    return 0;
}
