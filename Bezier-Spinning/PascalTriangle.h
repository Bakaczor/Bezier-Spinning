#pragma once

#include <QList>

/*!
 * \brief The PascalTriangle class
 * This class represents a Pascal's triangle with a certain number of levels.
 * It provides methods to get a specific row from the triangle.
 */
class PascalTriangle
{
  public:
    /*!
     * \brief Constructs a PascalTriangle object
     * \param levels The number of levels in the triangle
     */
    explicit PascalTriangle(int levels);
    /*!
     * \brief Returns a specific row from the Pascal's triangle
     * \param n The index of the row to return
     * \return A QList<int> representing the row at index n
     * \throws std::out_of_range If the requested row is out of the acceptable range
     */
    const QList<int>& getRow(int n) const;

  private:
    /*!
     * \brief The 2D list representing the Pascal's triangle
     */
    QList<QList<int>> m_triangle;
};
