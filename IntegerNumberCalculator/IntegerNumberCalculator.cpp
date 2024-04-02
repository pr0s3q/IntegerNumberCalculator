#include "iostream"

#include "Stack.h"

int main()
{
    Stack stack;
    stack.Push(3);
    stack.Push(9);
    stack.Push(15);
    stack.Push(43);
    std::cout << "Size: " << stack.Size() << "\n";
    while(!stack.IsEmpty())
    {
        std::cout << stack.Pop() << "\n";
    }
    return 0;
}