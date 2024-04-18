#include <iostream>
#include <string>

#include "CustomString.h"
#include "Operation.h"
#include "Stack.h"

#ifdef _DEBUG
CustomString debugString;
#endif

// ----------------------------------------------------------------------------

/// <summary>
/// Read data from console
/// </summary>
/// <returns></returns>
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

#ifdef _DEBUG
        debugString.Add(character);
#endif
    }

    return str;
}

// ----------------------------------------------------------------------------

/// <summary>
/// Add operation to CustomString
/// </summary>
/// <param name="str"></param>
/// <param name="stack"></param>
/// <param name="op"></param>
/// <param name="addStack">Determine, whether data from stack should be added to CustomString as well</param>
void AddOperationToStr(CustomString& str, Stack<int>& stack, const Operation* op, const bool addStack = true)
{
    op->AddToStr(str);
    if (addStack)
        stack.AddToStr(str);
}

// ----------------------------------------------------------------------------

/// <summary>
/// MIN operation
/// </summary>
/// <param name="stack">Data</param>
/// <param name="argCount">Number of operation arguments</param>
/// <returns>Minimal value of given arguments</returns>
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

/// <summary>
/// MAX operation
/// </summary>
/// <param name="stack"></param>
/// <param name="argCount">Number of operation arguments</param>
/// <returns>Maximal value of given arguments</returns>
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

/// <summary>
/// + operation (add two numbers from the top of the stack together)
/// </summary>
int Add(Stack<int>& stack)
{
    return stack.Pop() + stack.Pop();
}

// ----------------------------------------------------------------------------

/// <summary>
/// - operation (subtract two numbers from the top of the stack together)
/// </summary>
int Subtract(Stack<int>& stack)
{
    return stack.Pop() - stack.Pop();
}

// ----------------------------------------------------------------------------

/// <summary>
/// * operation (multiply two numbers from the top of the stack together)
/// </summary>
int Multiply(Stack<int>& stack)
{
    return stack.Pop() * stack.Pop();
}

// ----------------------------------------------------------------------------

/// <summary>
/// / operation (divide two numbers from the top of the stack together)
/// </summary>
int Divide(Stack<int>& stack)
{
    return stack.Pop() / stack.Pop(); //TODO: Handle dividing by 0
}

// ----------------------------------------------------------------------------

/// <summary>
/// Helper function for popping operation from top of the stack,
/// and adding data from it to operationOutput and postfixNotation
/// </summary>
/// <param name="stack"></param>
/// <param name="operationStack"></param>
/// <param name="postfixNotation"></param>
/// <param name="operationOutput"></param>
const Operation* PopOpAndAddToStr(
    Stack<int>& stack,
    Stack<Operation*>& operationStack,
    CustomString& postfixNotation,
    CustomString& operationOutput)
{
    const Operation* op = operationStack.Pop();
    AddOperationToStr(operationOutput, stack, op);
    AddOperationToStr(postfixNotation, stack, op, false);
    return op;
}

// ----------------------------------------------------------------------------

/// <summary>
/// Handle math operation (add, subtract, multiply, divide)
/// </summary>
/// <param name="stack"></param>
/// <param name="operationStack"></param>
/// <param name="postfixNotation"></param>
/// <param name="operationOutput"></param>
void HandleMathOperations(
    Stack<int>& stack,
    Stack<Operation*>& operationStack,
    CustomString& postfixNotation,
    CustomString& operationOutput)
{
    /// Helper local lambda function to either, add operation result to operationOutput or to the stack
    auto handleResult = [&stack, &operationStack, &operationOutput](const int opResult)
    {
        if (operationStack.IsEmpty())
            operationOutput.AddIntAsCharArr(opResult);

        else
        {
            stack.Push(opResult);
        }
    };

    auto handleOperation = [&stack, &operationStack, &postfixNotation, &operationOutput, &handleResult]
    (int(*func)(Stack<int>&))
    {
        const auto op = PopOpAndAddToStr(stack, operationStack, postfixNotation, operationOutput);
        delete op;
        const int opResult = func(stack);
        handleResult(opResult);
    };

    operationStack.Peek()->IncrementArgCount();
    const Operation::Type opType = operationStack.Peek()->GetType();
    switch (opType)
    {
    case Operation::ADD:
        handleOperation(&Add);
        break;
    case Operation::SUB:
        handleOperation(&Subtract);
        break;
    case Operation::MUL:
        handleOperation(&Multiply);
        break;
    case Operation::DIV:
        handleOperation(&Divide);
        break;
    case Operation::NAO:
    case Operation::MIN:
    case Operation::MAX:
    case Operation::OB:
    case Operation::CB:
    case Operation::NA:
        break;
    }
}

// ----------------------------------------------------------------------------

/// <summary>
/// Main loop, reading data from console, converting, and processing data from input
/// </summary>
void ReadLineLoop()
{
    Stack<int> stack;
    Stack<Operation*> operationStack;
    CustomString* str;
    CustomString postfixNotation(100);
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
            case Operation::ADD:
            case Operation::SUB:
            case Operation::MUL:
            case Operation::DIV:
                {
                    operationStack.Push(new Operation(type));
                    break;
                }
            case Operation::OB:
                {
                    if (operationStack.IsEmpty())
                        break;

                    operationStack.Peek()->AddBracket();
                    break;
                }
            case Operation::NA:
                continue;
            case Operation::CB:
                {
                    if (operationStack.IsEmpty())
                        break;

                    operationStack.Peek()->RemoveBracket();
                    if (operationStack.Peek()->GetNumberOfBrackets() != 0)
                        break;

                    const Operation* op = PopOpAndAddToStr(stack, operationStack, postfixNotation, operationOutput);
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
                    case Operation::ADD:
                    case Operation::SUB:
                    case Operation::MUL:
                    case Operation::DIV:
                        HandleMathOperations(stack, operationStack, postfixNotation, operationOutput);
                        break;
                    }

                    if (operationStack.IsEmpty())
                        operationOutput.AddIntAsCharArr(opResult);
                    else
                    {
                        stack.Push(opResult);
                        operationStack.Peek()->IncrementArgCount();
                    }

                    delete op;
                    break;
                }
            case Operation::NAO:
                {
                    const int number = str->ToInt();
                    stack.Push(number);

                    postfixNotation.AddIntAsCharArr(number);
                    postfixNotation.Add(' ');

                    if (!operationStack.IsEmpty())
                        HandleMathOperations(stack, operationStack, postfixNotation, operationOutput);

                    break;
                }
            }
        }

        delete str;
    }

    if (!operationStack.IsEmpty())
        HandleMathOperations(stack, operationStack, postfixNotation, operationOutput);

    postfixNotation.Print();
    CustomString::PrintNewLine();
    operationOutput.Print();
    CustomString::PrintNewLine();
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