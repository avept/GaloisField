#include <iostream>
#include <GaloisField.h>

int main()
{
    GaloisField element1("110");
    GaloisField element2("101");

    std::cout << element1 + element2 << std::endl;
    std::cout << "sqaure: " << GaloisField::square(element1) << std::endl;
    std::cout << "trace a: " << GaloisField::trace(element2) << std::endl;
    std::cout << "inverse: " << GaloisField::inverse(element1) << std::endl;
    std::cout << "power: " << element1.power(element2);
    return 0;
}