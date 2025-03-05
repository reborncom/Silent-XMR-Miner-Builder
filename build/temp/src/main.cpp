#include <windows.h>
#include <iostream>
#include "myfunctions.h"

int main()
{
    std::cout << "Hello from main.cpp!" << std::endl;
    printMessage();

    std::cin.get();
    return 0;
}