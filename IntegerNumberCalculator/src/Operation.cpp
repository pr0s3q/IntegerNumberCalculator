#include "Operation.h"

#include <iostream>

#include "CustomString.h"

// ----------------------------------------------------------------------------

Operation::Operation(const Type type)
    : m_type(type), m_argCount(0)
{
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

void Operation::Print() const
{
    PrintType();
    std::cout << m_argCount << " ";
}

// ----------------------------------------------------------------------------

void Operation::PrintType() const
{
    switch (m_type)
    {
    case NAO:
    case OB:
    case CB:
    case NA:
        break;
    case MIN:
        std::cout << "MIN";
        break;
    case MAX:
        std::cout << "MAX";
        break;
    }
}

// ----------------------------------------------------------------------------