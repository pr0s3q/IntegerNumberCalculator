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

    void Add(const char* item, const int itemSize);

    // ----------------------------------------------------------------------------

    void Add(int item);

    // ----------------------------------------------------------------------------

    void AddIntAsCharArr(const int number);

    // ----------------------------------------------------------------------------

    bool Equals(const char* charArr, const int& len) const;

    // ----------------------------------------------------------------------------

    bool IsEmpty() const;

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Print internal string to console
    /// </summary>
    void Print() const;

    // ----------------------------------------------------------------------------

    static void PrintNewLine();

    // ----------------------------------------------------------------------------

    int ToInt() const;

    // ----------------------------------------------------------------------------

private:
    // ----------------------------------------------------------------------------

    char* m_internalString;
    int m_size;
    int m_capacity;

    // ----------------------------------------------------------------------------
};