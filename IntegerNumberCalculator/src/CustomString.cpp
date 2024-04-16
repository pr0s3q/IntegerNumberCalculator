#include "CustomString.h"

#include <iostream>

// ----------------------------------------------------------------------------

CustomString::CustomString()
    : m_internalString(new char[0]), m_size(0), m_capacity(0)
{
}

// ----------------------------------------------------------------------------

CustomString::CustomString(const int capacity)
    : m_internalString(new char[capacity]{0}), m_size(0), m_capacity(capacity)
{
}

// ----------------------------------------------------------------------------

void CustomString::Add(const char item)
{
    if (m_size == m_capacity) // No more space - expand
    {
        int newSize;
        if (m_capacity == 0) // Initialize with size 1 - since 0 * 1.5 will give 0
            newSize = 1;
        else if (m_capacity == 1)
            newSize = 2; // Initialize with size 2 - since 1 * 1.5 will give 1
        else
            newSize = static_cast<int>(m_capacity * 1.5);

        const auto temp = new char[newSize + 1]{0}; // Dynamically allocate based on newSize (add + 1 for EOL character)
        for (int i = 0; i < m_size; ++i)
        {
            temp[i] = m_internalString[i]; // Copy values from old string to new one
        }

        delete[] m_internalString; // Delete old string
        m_internalString = temp; // Assign new string
        m_capacity = newSize;
    }

    m_internalString[m_size] = item;
    ++m_size;
}

// ----------------------------------------------------------------------------

void CustomString::Add(const int item)
{
    const char charItem = static_cast<char>(item);
    Add(charItem);
}

// ----------------------------------------------------------------------------

bool CustomString::Equals(const char* charArr, const int& len) const
{
    if (m_size != len)
        return false;

    for (int i = 0; i < len; ++i)
    {
        if (m_internalString[i] != charArr[i])
            return false;
    }

    return true;
}

// ----------------------------------------------------------------------------

bool CustomString::IsEmpty() const
{
    return m_capacity == 0;
}

// ----------------------------------------------------------------------------

void CustomString::Print() const
{
    std::cout << m_internalString << " ";
}

// ----------------------------------------------------------------------------

void CustomString::PrintNewLine()
{
    std::cout << "\n";
}

// ----------------------------------------------------------------------------

int CustomString::ToInt() const
{
    return strtol(m_internalString, nullptr, 10);
}

// ----------------------------------------------------------------------------