#include "Operation.h"

#include <iostream>

#include "CustomString.h"

// ----------------------------------------------------------------------------

Operation::Operation(const Type type)
    : m_type(type), m_argCount(0), m_numberOfBrackets(0)
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
    }
}

// ----------------------------------------------------------------------------