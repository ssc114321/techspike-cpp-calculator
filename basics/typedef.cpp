#include <iostream>
#include <vector>

// typedef std::vector<std::pair<std::string, int>> pairlist_t;
typedef std::string text_t;
using number_t = int; // 'using' keyword is more commonly used

int main() {

    // pairlist_t pairlist;
    text_t firstName = "Bro";
    number_t age = 21;

    std::cout << firstName << '\n';
    std::cout << age;

    return 0;
}