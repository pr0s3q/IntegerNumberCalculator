#pragma once

struct CustomString;

/// <summary>
/// Stack struct made as linked list
/// </summary>
template <typename T>
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
        explicit Node(T value) : m_value(value), m_nextNode(nullptr)
        {
        }

        T m_value;
        Node* m_nextNode;
    };

    // ----------------------------------------------------------------------------

public:

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Default constructor
    /// </summary>
    Stack() : m_lastNode(nullptr)
    {
    }

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Add stack data to CustomString
    /// </summary>
    void AddToStr(CustomString& str)
    {
        const Node* node = m_lastNode;
        while (node)
        {
            str.AddIntAsCharArr(node->m_value);
            str.Add(' ');
            node = node->m_nextNode;
        }

        str.Add(10);
    }

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Check, whether stack is empty
    /// </summary>
    /// <returns>True, if stack is empty, false otherwise</returns>
    bool IsEmpty() const
    {
        return !m_lastNode;
    }

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Push value at the end of the stack
    /// </summary>
    /// <param name="value">Value, pushed at the end of the stack</param>
    void Push(T value)
    {
        Node* previousLastNode = m_lastNode;
        m_lastNode = new Node(value);
        if (previousLastNode)
        {
            m_lastNode->m_nextNode = previousLastNode;
        }
    }

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Peek element on top of the stack
    /// </summary>
    T Peek()
    {
        return m_lastNode->m_value;
    }

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Pop last element from the stack
    /// </summary>
    /// <returns>Popped value</returns>
    T Pop()
    {
        const Node* previousLastNode = m_lastNode;
        m_lastNode = previousLastNode->m_nextNode;
        const T value = previousLastNode->m_value;
        delete previousLastNode;
        return value;
    }

    // ----------------------------------------------------------------------------

    /// <summary>
    /// Returns size of the stack
    /// </summary>
    int Size() const
    {
        int size = 0;
        const Node* node = m_lastNode;
        while (node)
        {
            ++size;
            node = node->m_nextNode;
        }

        return size;
    }

    // ----------------------------------------------------------------------------

private:

    // ----------------------------------------------------------------------------

    Node* m_lastNode;

    // ----------------------------------------------------------------------------
};