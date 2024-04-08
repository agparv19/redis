#include <iostream>
#include <vector>
#include <memory>

int main() {
    std::vector<std::unique_ptr<int>> vec;

    // Fill the vector with some unique_ptrs
    vec.push_back(std::make_unique<int>(1));
    vec.push_back(std::make_unique<int>(2));
    vec.push_back(std::make_unique<int>(3));

    // Iterating over the vector
    for (const auto& ptr : vec) {
        std::cout << *ptr << std::endl; // Dereference the unique_ptr to access the object
    }

    return 0;
}