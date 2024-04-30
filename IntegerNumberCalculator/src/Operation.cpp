#include "Operation.h"

#include "CustomString.h"

// ----------------------------------------------------------------------------

Operation::Operation(const Type type)
    : m_type(type)
    , m_argCount(0)
    , m_numberOfBrackets(0)
{
}

// ----------------------------------------------------------------------------

void Operation::AddBracket()
{
    ++m_numberOfBrackets;
}

// ----------------------------------------------------------------------------

Operation::Type Operation::DetermineType(const CustomString* str)
{
    if (str->Equals("MIN", 3))
        return MIN;
    if (str->Equals("MAX", 3))
        return MAX;
    if (str->Equals("+", 1))
        return ADD;
    if (str->Equals("-", 1))
        return SUB;
    if (str->Equals("*", 1))
        return MUL;
    if (str->Equals("N", 1))
        return N;
    if (str->Equals("/", 1))
        return DIV;
    if (str->Equals("(", 1))
        return OB;
    if (str->Equals(")", 1))
        return CB;
    if (str->Equals(",", 1))
        return NA;
    if (str->Equals("IF", 2))
        return IF;

    return NAO;
}

// ----------------------------------------------------------------------------

int Operation::GetArgCount() const
{
    return m_argCount;
}

// ----------------------------------------------------------------------------

int Operation::GetNumberOfBrackets() const
{
    return m_numberOfBrackets;
}

// ----------------------------------------------------------------------------

Operation::Type Operation::GetType() const
{
    return m_type;
}

// ----------------------------------------------------------------------------

void Operation::IncrementArgCount()
{
    ++m_argCount;
}

// ----------------------------------------------------------------------------

bool Operation::IsOfMathType(Type type)
{
    if (type == ADD ||
        type == SUB ||
        type == MUL ||
        type == DIV)
        return true;

    return false;
}

// ----------------------------------------------------------------------------

bool Operation::IsOfNoBracketType(const Type type)
{
    if (type == ADD ||
        type == SUB ||
        type == MUL ||
        type == DIV ||
        type == N)
        return true;

    return false;
}

// ----------------------------------------------------------------------------

void Operation::RemoveBracket()
{
    if (m_numberOfBrackets == 0)
        return;

    --m_numberOfBrackets;
}

// ----------------------------------------------------------------------------

void Operation::AddToStr(CustomString& str) const
{
    AddType(str);
    if (m_type == MIN || m_type == MAX)
        str.AddIntAsCharArr(m_argCount);
    str.Add(' ');
}

// ----------------------------------------------------------------------------

int Operation::BiggerPriority(const Type firstType, const Type secondType)
{
    const int firstTypePriority = GetOperationTypePriority(firstType);
    const int secondTypePriority = GetOperationTypePriority(secondType);

    if (firstTypePriority > secondTypePriority)
        return 1;

    if (firstTypePriority < secondTypePriority)
        return -1;

    return 0;
}

// ----------------------------------------------------------------------------

void Operation::DecrementArgCount()
{
    --m_argCount;
}

// ----------------------------------------------------------------------------

void Operation::AddType(CustomString& str) const
{
    switch (m_type)
    {
    case NAO:
    case OB:
    case CB:
    case NA:
        break;
    case MIN:
        str.Add("MIN", 3);
        break;
    case MAX:
        str.Add("MAX", 3);
        break;
    case ADD:
        str.Add("+", 1);
        break;
    case SUB:
        str.Add("-", 1);
        break;
    case MUL:
        str.Add("*", 1);
        break;
    case DIV:
        str.Add("/", 1);
        break;
    case N:
        str.Add("N", 1);
        break;
    case IF:
        str.Add("IF", 2);
        break;
    }
}

// ----------------------------------------------------------------------------

int Operation::GetOperationTypePriority(const Type type)
{
    switch (type)
    {
    case NAO:
    case OB:
    case CB:
    case NA:
        return -1;
    case ADD:
    case SUB:
        return 0;
    case MUL:
    case DIV:
        return 1;
    case IF:
        return 2;
    case N:
        return 3;
    case MIN:
    case MAX:
        return 4;
    }

    return -1;
}

// ----------------------------------------------------------------------------