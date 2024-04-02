#pragma once

/// <summary>
/// Stack struct made as linked list
/// </summary>
struct Stack
{
private:

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Internal Node class, that contains value, and pointer to next node.
    /// If m_nextNode is nullptr, there is no more nodes, and current one is the last one
    /// </summary>
    struct Node
    {
        Node(int value);
        int m_value;
        Node* m_nextNode;
    };

    // ----------------------------------------------------------------------------

public:

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Default constructor
    /// </summary>
    Stack();

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Check, whether stack is empty
    /// </summary>
    /// <returns>True, if stack is empty, false otherwise</returns>
    bool IsEmpty() const;

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Push value at the end of the stack
    /// </summary>
    /// <param name="value">Value, pushed at the end of the stack</param>
    void Push(const int value);

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Pop last element from the stack
    /// </summary>
    /// <returns>Popped value</returns>
    int Pop();

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Returns size of the stack
    /// </summary>
    int Size() const;

    // ----------------------------------------------------------------------------

private:

    Node* m_lastNode;

    // ----------------------------------------------------------------------------
};