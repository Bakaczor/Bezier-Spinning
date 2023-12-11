#include <stdexcept>

#include "PascalTriangle.h"

PascalTriangle::PascalTriangle(int levels)
{
    m_triangle.reserve(levels);
    m_triangle.append({1, 1});
    for (int i = 1; i < levels; i++)
    {
        int n = i + 2;
        m_triangle.append(QList<int>(n));
        for (int j = 0; j < n; j++)
        {
            if (j == 0 || j == n - 1)
            {
                m_triangle[i][j] = 1;
            }
            else
            {
                m_triangle[i][j] = m_triangle[i - 1][j - 1] + m_triangle[i - 1][j];
            }
        }
    }
}

const QList<int>& PascalTriangle::getRow(int n) const
{
    if (n - 1 < 0 || n - 1 >= m_triangle.count())
    {
        throw std::out_of_range("Requested row was out of acceptable range");
    }
    return m_triangle[n - 1];
}
