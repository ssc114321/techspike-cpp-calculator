#include <iostream>

int main() {

    std::string name;

    std::cout << "What's your name?: ";
    std::cin >> name;

    std::cout << "Hello " << name << '\n';

    std::string fullName;
    std::cout << "What's your full name?: ";
    std::getline(std::cin >> std::ws, fullName);

    std::cout << "Hello " << fullName;
    return 0;
}