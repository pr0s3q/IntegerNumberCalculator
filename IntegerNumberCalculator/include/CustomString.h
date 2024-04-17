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
    explicit CustomString(int capacity);

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Add char to internal string
    /// </summary>
    /// <param name="item">Char to add</param>
    void Add(char item);

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Add chars to internal string
    /// </summary>
    /// <param name="item">Chars to add</param>
    /// <param name="itemSize">Number of characters</param>
    void Add(const char* item, int itemSize);

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Add char in ASCII standard to internal string
    /// </summary>
    /// <param name="item">Char in ASCII standard</param>
    void Add(int item);

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Add int to internal string. Convert int to char first (10 -> "10")
    /// </summary>
    void AddIntAsCharArr(int number);

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Check, whether CustomString data is equal to charArr data
    /// </summary>
    /// <param name="charArr">Data to check</param>
    /// <param name="len">Number of characters to check</param>
    /// <returns>True if equal, false otherwise</returns>
    bool Equals(const char* charArr, const int& len) const;

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Check, whether CustomString is empty
    /// </summary>
    /// <returns>True if empty, false otherwise</returns>
    bool IsEmpty() const;

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Print internal string to console
    /// </summary>
    void Print() const;

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Print new line in console
    /// </summary>
    static void PrintNewLine();

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Convert CustomString to int
    /// </summary>
    /// <returns>Converted int result</returns>
    int ToInt() const;

    // ----------------------------------------------------------------------------

private:
    // ----------------------------------------------------------------------------

    char* m_internalString;
    int m_size;
    int m_capacity;

    // ----------------------------------------------------------------------------
};