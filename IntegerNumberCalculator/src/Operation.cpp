#include "Operation.h"

#include "CustomString.h"

// ----------------------------------------------------------------------------

Operation::Operation(const Type type, const int bracketLevel)
    : m_type(type)
    , m_argCount(0)
    , m_bracketLevel(bracketLevel)
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

    return NAO;
}

// ----------------------------------------------------------------------------

int Operation::GetArgCount() const
{
    return m_argCount;
}

// ----------------------------------------------------------------------------

int Operation::GetBracketLevel() const
{
    return m_bracketLevel;
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

void Operation::RemoveBracket()
{
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
    }
}

// ----------------------------------------------------------------------------