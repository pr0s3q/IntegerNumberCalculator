#include "Stack.h"

// ----------------------------------------------------------------------------

Stack::Stack()
    : m_lastNode(nullptr)
{
}

// ----------------------------------------------------------------------------

bool Stack::IsEmpty() const
{
    return !m_lastNode;
}

// ----------------------------------------------------------------------------

void Stack::Push(const int value)
{
    Node* previousLastNode = m_lastNode;
    m_lastNode = new Node(value);
    if(previousLastNode)
    {
        m_lastNode->m_nextNode = previousLastNode;
    }
}

// ----------------------------------------------------------------------------

int Stack::Pop()
{
    const Node* previousLastNode = m_lastNode;
    m_lastNode = previousLastNode->m_nextNode;
    const int value = previousLastNode->m_value;
    delete previousLastNode;
    return value;
}

// ----------------------------------------------------------------------------

int Stack::Size() const
{
    int size = 0;
    const Node* node = m_lastNode;
    while(node)
    {
        ++size;
        node = node->m_nextNode;
    }
    return size;
}

// ----------------------------------------------------------------------------

Stack::Node::Node(const int value)
    : m_value(value), m_nextNode(nullptr)
{
}

// ----------------------------------------------------------------------------