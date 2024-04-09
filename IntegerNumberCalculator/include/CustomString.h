#pragma once

/// <summary>
/// Custom string struct
/// </summary>
struct CustomString
{

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Default constructor - initialize with capacity 0
    /// </summary>
    CustomString();

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Initialize class with specific capacity
    /// </summary>
    /// <param name="capacity"></param>
    CustomString(int capacity);

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Add char to internal string
    /// </summary>
    /// <param name="item">Char to add</param>
    void Add(char item);

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Print internal string to console
    /// </summary>
    void Print() const;

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Read line to internal string
    /// </summary>
    void ReadLine();

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Add char to internal string
    /// </summary>
    /// <param name="item">Char to add</param>
    void operator +=(char item);

    // ----------------------------------------------------------------------------

private:

    // ----------------------------------------------------------------------------

    char* m_internalString;
    int m_size;
    int m_capacity;

    // ----------------------------------------------------------------------------
};