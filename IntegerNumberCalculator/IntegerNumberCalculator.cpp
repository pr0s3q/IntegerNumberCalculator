#include <string>

#include "CustomString.h"
#include "iostream"

int main()
{

    int value;
    std::cin >> value;
    CustomString* string = new CustomString[value];
    for(int i = 0; i < value; ++i)
    {
        string[i].ReadLine();
    }

    for(int i = 0; i < value; ++i)
    {
        string[i].Print();
    }

    return 0;
}