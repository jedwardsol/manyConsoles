#include "console.h"
#include <array>
#include <string>
#include <iostream>

int main()
{

    auto consoles = std::array<Console,3>{};


    for(int i=0;i<1000;i++)
    {
        consoles[i%3] << i << '\n';
    }


    auto dummy=std::string{};
    std::getline(std::cin,dummy);

}