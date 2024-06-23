#pragma once

#include <QList>

/*!
 * \brief The Circle class
 * This class represents a circle with a certain number of degrees.
 * It provides methods to get the current and next degree on the circle.
 */
class Circle
{
  public:
    /*!
     * \brief Constructs a Circle object
     * \param count The number of degrees on the circle
     */
    explicit Circle(int count = 120);
    /*!
     * \brief Returns the current degree on the circle
     * \return A float representing the current degree on the circle
     */
    float current() const;
    /*!
     * \brief Moves to the next degree on the circle and returns it
     * \return A float representing the next degree on the circle
     */
    float next();

  private:
    /*!
     * \brief The current index
     */
    int m_i;
    /*!
     * \brief The total number of degrees on the circle
     */
    int m_count;
    /*!
     * \brief A list of degrees on the circle
     */
    QList<float> m_degrees;
};
