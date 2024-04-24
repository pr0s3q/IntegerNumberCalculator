#pragma once

struct CustomString;

/// <summary>
/// Represent operation
/// </summary>
struct Operation
{
    // ----------------------------------------------------------------------------

    /// <summary>
    /// Types of operation
    /// </summary>
    enum Type
    {
        // Not an operation
        NAO,
        MIN,
        MAX,
        // +
        ADD,
        // -
        SUB,
        // *
        MUL,
        // /
        DIV,
        // Unary negation
        N,
        // Opening bracket -> (
        OB,
        // Closing bracket -> )
        CB,
        // Next argument
        NA
    };

    // ----------------------------------------------------------------------------

    explicit Operation(Type type);

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Increment number of bracket in operation
    /// </summary>
    void AddBracket();

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Add operation data to string
    /// </summary>
    void AddToStr(CustomString& str) const;

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Determine operation type, based on string input
    /// </summary>
    static Type DetermineType(const CustomString* str);

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Get number of operation arguments
    /// </summary>
    int GetArgCount() const;

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Get number of brackets in operation
    /// </summary>
    /// <returns></returns>
    int GetNumberOfBrackets() const;

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Get operation type
    /// </summary>
    Type GetType() const;

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Increment number of arguments in operation
    /// </summary>
    void IncrementArgCount();

    // ----------------------------------------------------------------------------
    /// <summary>
    /// Decrement number of bracket in operation
    /// </summary>
    void RemoveBracket();

    // ----------------------------------------------------------------------------

private:

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Add operation type
    /// </summary>
    void AddType(CustomString& str) const;

    // ----------------------------------------------------------------------------

    Type m_type;
    int m_argCount;
    int m_numberOfBrackets;

    // ----------------------------------------------------------------------------
};