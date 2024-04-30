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
        IF,
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
    /// Check, which operation have bigger priority
    /// </summary>
    /// <returns>
    /// - 1, if first have bigger priority.
    /// - 0, if priority is the same
    /// - -1, if second have bigger priority
    /// </returns>
    static int BiggerPriority(Type firstType, Type secondType);

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Decrement number of arguments in operation
    /// </summary>
    void DecrementArgCount();

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
    /// Check, if operation is of math type (+, -, /, *)
    /// </summary>
    static bool IsOfMathType(Type type);

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Check, if operation is of no bracket type (+, -, /, *, N)
    /// </summary>
    static bool IsOfNoBracketType(Type type);

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

    /// <summary>
    ///
    /// </summary>
    static int GetOperationTypePriority(Type type);

    // ----------------------------------------------------------------------------

    Type m_type;
    int m_argCount;
    int m_numberOfBrackets;

    // ----------------------------------------------------------------------------
};