#include <QtMath>

#include "Circle.h"

Circle::Circle(int count) : m_i(0), m_count(count)
{
    float d = 2 * M_PI / count;

    m_degrees = QList<float>(count);
    m_degrees[0] = 0;
    for (int i = 1; i < count; i++)
    {
        m_degrees[i] = m_degrees[i - 1] + d;
    }
}

float Circle::current() const
{
    return m_degrees.at(m_i);
}

float Circle::next()
{
    m_i = (m_i + 1) % m_count;
    return current();
}
