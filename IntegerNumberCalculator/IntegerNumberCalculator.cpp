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
    return -stack.Pop() + stack.Pop();
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
    const int firstNum = stack.Pop();
    return stack.Pop() / firstNum; //TODO: Handle dividing by 0
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
bool HandleMathOperations(
    Stack<int>& stack,
    Stack<Operation*>& operationStack,
    CustomString& postfixNotation,
    CustomString& operationOutput)
{
    auto handleOperation = [&stack, &operationStack, &postfixNotation, &operationOutput]
    (int (*func)(Stack<int>&))
    {
        const auto op = PopOpAndAddToStr(stack, operationStack, postfixNotation, operationOutput);
        const int opResult = func(stack);
        stack.Push(opResult);
        delete op;
    };

    if (operationStack.Peek()->GetNumberOfBrackets() != 0)
        return false;

    const Operation::Type opType = operationStack.Peek()->GetType();
    switch (opType)
    {
    case Operation::ADD:
        handleOperation(&Add);
        return true;
    case Operation::SUB:
        handleOperation(&Subtract);
        return true;
    case Operation::MUL:
        handleOperation(&Multiply);
        return true;
    case Operation::DIV:
        handleOperation(&Divide);
        return true;
    case Operation::NAO:
    case Operation::MIN:
    case Operation::MAX:
    case Operation::N:
    case Operation::OB:
    case Operation::CB:
    case Operation::NA:
    case Operation::IF:
        break;
    }

    return false;
}

// ----------------------------------------------------------------------------

bool HandleNegation(
    Stack<int>& stack,
    Stack<Operation*>& operationStack,
    CustomString& postfixNotation,
    CustomString& operationOutput)
{
    if (operationStack.Peek()->GetType() != Operation::N)
        return false;

    if (operationStack.Peek()->GetArgCount() == 0)
        return false;

    const auto op = PopOpAndAddToStr(stack, operationStack, postfixNotation, operationOutput);
    delete op;
    const int opResult = -stack.Pop();

    stack.Push(opResult);
    if (!operationStack.IsEmpty())
        operationStack.Peek()->IncrementArgCount();

    return true;
}

// ----------------------------------------------------------------------------

void HandleIf(
    Stack<int>& stack,
    Stack<Operation*>& operationStack,
    CustomString& postfixNotation,
    CustomString& operationOutput)
{
    if (operationStack.Peek()->GetType() != Operation::IF)
        return;

    if (operationStack.Peek()->GetArgCount() != 3)
        return;

    const auto op = PopOpAndAddToStr(stack, operationStack, postfixNotation, operationOutput);
    delete op;

    const int c = stack.Pop();
    const int b = stack.Pop();
    const int a = stack.Pop();
    int opResult;
    if (a > 0)
        opResult = b;
    else
        opResult = c;

    stack.Push(opResult);
    if (!operationStack.IsEmpty())
        operationStack.Peek()->IncrementArgCount();
}

// ----------------------------------------------------------------------------

void HandleOperation(
    Stack<int>& stack,
    Stack<Operation*>& operationStack,
    CustomString& postfixNotation,
    CustomString& operationOutput)
{
    if (operationStack.IsEmpty() || operationStack.Peek()->GetNumberOfBrackets() != 0)
        return;

    int opResult = 0;

    switch (operationStack.Peek()->GetType())
    {
    case Operation::NAO:
    case Operation::OB:
    case Operation::CB:
    case Operation::NA:
        break;
    case Operation::MIN:
        {
            const Operation* op = PopOpAndAddToStr(stack, operationStack, postfixNotation, operationOutput);
            opResult = Min(stack, op->GetArgCount());
            delete op;
            break;
        }
    case Operation::MAX:
        {
            const Operation* op = PopOpAndAddToStr(stack, operationStack, postfixNotation, operationOutput);
            opResult = Max(stack, op->GetArgCount());
            delete op;
            break;
        }
    case Operation::ADD:
    case Operation::SUB:
    case Operation::MUL:
    case Operation::DIV:
        HandleMathOperations(stack, operationStack, postfixNotation, operationOutput);
        return;
    case Operation::N:
        HandleNegation(stack, operationStack, postfixNotation, operationOutput);
        return;
    case Operation::IF:
        HandleIf(stack, operationStack, postfixNotation, operationOutput);
        return;
    }

    stack.Push(opResult);
    if (!operationStack.IsEmpty())
        operationStack.Peek()->IncrementArgCount();
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
    Operation::Type currentOperation = Operation::NAO;
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
            case Operation::N:
            case Operation::IF:
                {
                    while (Operation::IsOfNoBracketType(currentOperation) &&
                        Operation::BiggerPriority(currentOperation, type) != -1)
                    {
                        if (stack.IsEmpty())
                            break;

                        const int beforeHandlingSize = operationStack.Size();
                        HandleOperation(stack, operationStack, postfixNotation, operationOutput);
                        if (beforeHandlingSize == operationStack.Size() ||
                            operationStack.IsEmpty())
                            break;

                        currentOperation = operationStack.Peek()->GetType();
                    }

                    operationStack.Push(new Operation(type));
                    currentOperation = type;
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
                while (Operation::IsOfNoBracketType(currentOperation))
                {
                    const int beforeHandlingSize = operationStack.Size();
                    HandleOperation(stack, operationStack, postfixNotation, operationOutput);
                    if (beforeHandlingSize == operationStack.Size() ||
                        operationStack.IsEmpty())
                        break;

                    currentOperation = operationStack.Peek()->GetType();
                }
                HandleOperation(stack, operationStack, postfixNotation, operationOutput);
                break;
            case Operation::CB:
                {
                    if (operationStack.IsEmpty())
                        break;

                    if (Operation::IsOfNoBracketType(currentOperation))
                    {
                        bool bracketDecremented = operationStack.Peek()->GetNumberOfBrackets() > 0;
                        operationStack.Peek()->RemoveBracket();
                        if (operationStack.Peek()->GetNumberOfBrackets() != 0)
                            break;

                        while (true)
                        {
                            const int beforeHandlingSize = operationStack.Size();
                            HandleOperation(stack, operationStack, postfixNotation, operationOutput);
                            if (beforeHandlingSize == operationStack.Size() ||
                                operationStack.IsEmpty())
                                break;
                        }

                        if (operationStack.IsEmpty())
                            break;

                        if (!bracketDecremented)
                            operationStack.Peek()->RemoveBracket();
                        currentOperation = operationStack.Peek()->GetType();
                        break;
                    }

                    operationStack.Peek()->RemoveBracket();
                    if (operationStack.Peek()->GetNumberOfBrackets() != 0)
                        break;

                    HandleOperation(stack, operationStack, postfixNotation, operationOutput);
                    if (!operationStack.IsEmpty())
                        currentOperation = operationStack.Peek()->GetType();
                    else
                        currentOperation = Operation::NAO;

                    break;
                }
            case Operation::NAO:
                {
                    const int number = str->ToInt();
                    stack.Push(number);

                    postfixNotation.AddIntAsCharArr(number);
                    postfixNotation.Add(' ');

                    if (!operationStack.IsEmpty())
                    {
                        currentOperation = operationStack.Peek()->GetType();
                        operationStack.Peek()->IncrementArgCount();
                    }

                    break;
                }
            }
        }

        delete str;
    }

    while (!operationStack.IsEmpty())
        HandleOperation(stack, operationStack, postfixNotation, operationOutput);

    if (!stack.IsEmpty())
        operationOutput.AddIntAsCharArr(stack.Pop());

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