#include <iostream>
#include <string>

#include "CustomString.h"
#include "Operation.h"
#include "Stack.h"

// ----------------------------------------------------------------------------

CustomString* Read()
{
    const auto str = new CustomString;
    int character;
    while ((character = getchar()) != ' ')
    {
        if (character == '.')
            return nullptr;

        if (character == 10)
            continue;

        str->Add(character);
    }
    return str;
}

// ----------------------------------------------------------------------------

void AddOperationToStr(CustomString& str, Stack<int>& stack, const Operation* op)
{
    op->AddToStr(str);
    stack.AddToStr(str);
}

// ----------------------------------------------------------------------------

void AddFormulaResult(CustomString& str, const int result)
{
    str.AddIntAsCharArr(result);
}

// ----------------------------------------------------------------------------

int Min(Stack<int>& stack, int argCount)
{
    --argCount;
    int min = stack.Pop();
    while (argCount > 0)
    {
        const int temp = stack.Pop();
        if (temp < min)
            min = temp;

        --argCount;
    }

    return min;
}

// ----------------------------------------------------------------------------

int Max(Stack<int>& stack, int argCount)
{
    --argCount;
    int max = stack.Pop();
    while (argCount > 0)
    {
        const int temp = stack.Pop();
        if (temp > max)
            max = temp;

        --argCount;
    }

    return max;
}

// ----------------------------------------------------------------------------

void ReadLineLoop()
{
    Stack<int> stack;
    Stack<Operation*> operationStack;
    CustomString* str;
    CustomString operationOutput(100);
    while ((str = Read()) != nullptr)
    {
        if (!str->IsEmpty())
        {
            const Operation::Type type = Operation::DetermineType(str);
            switch (type)
            {
            case Operation::MIN:
            case Operation::MAX:
                operationStack.Push(new Operation(type));
                break;
            case Operation::OB:
            case Operation::NA:
                continue;
            case Operation::CB:
                {
                    const Operation* op = operationStack.Pop();
                    AddOperationToStr(operationOutput, stack, op);
                    int opResult = 0;
                    switch (op->GetType())
                    {
                    case Operation::NAO:
                    case Operation::OB:
                    case Operation::CB:
                    case Operation::NA:
                        break;
                    case Operation::MIN:
                        opResult = Min(stack, op->GetArgCount());
                        break;
                    case Operation::MAX:
                        opResult = Max(stack, op->GetArgCount());
                        break;
                    }
                    if (operationStack.IsEmpty())
                        AddFormulaResult(operationOutput, opResult);
                    else
                    {
                        stack.Push(opResult);
                        operationStack.Peek()->IncrementArgCount();
                    }
                    delete op;
                    break;
                }
            case Operation::NAO:
                const int number = str->ToInt();
                stack.Push(number);
                operationStack.Peek()->IncrementArgCount();
                break;
            }
        }

        delete str;
    }

    operationOutput.Print();
}

// ----------------------------------------------------------------------------

int main()
{
    int value;
    std::cin >> value;
    for (int i = 0; i < value; ++i)
    {
        CustomString::PrintNewLine();
        ReadLineLoop();
    }

    return 0;
}

// ----------------------------------------------------------------------------