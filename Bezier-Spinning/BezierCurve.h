#pragma once

#include <QPainter>
#include <QColor>
#include <QPoint>
#include <QSize>
#include <QtMath>

#include "PascalTriangle.h"

/*!
 * \brief The BezierCurve class
 * This class represents a Bezier curve.
 * It provides methods to generate the curve, select and drag control points, and paint the curve.
 */
class BezierCurve
{
  public:
    /*!
     * \brief Constructs a BezierCurve object
     * \param triangle The Pascal's triangle used for the curve calculation
     * \param count The number of control points for the curve
     */
    explicit BezierCurve(PascalTriangle triangle, int count = 3);
    /*!
     * \brief Generates the Bezier curve
     * \param count The number of control points for the curve
     */
    void generate(int count);
    /*!
     * \brief Selects a control point
     * \param x The x-coordinate of the point to select
     * \param y The y-coordinate of the point to select
     */
    void select(const int& x, const int& y);
    /*!
     * \brief Drags a control point
     * \param x The x-coordinate of the point to drag
     * \param y The y-coordinate of the point to drag
     */
    void drag(const int& x, const int& y);
    /*!
     * \brief Paints the Bezier curve
     * \param painter The QPainter object used for painting
     * \param drawPolyline A boolean indicating whether to draw the polyline
     */
    void paint(QPainter& painter, const bool& drawPolyline) const;
    /*!
     * \brief Returns the angle between x-axis and tangent vector at the current point of Bezier curve
     * \return A float representing the current angle of the Bezier curve
     */
    float currentAngle() const;
    /*!
     * \brief Returns the first control point of the Bezier curve
     * \return A QPoint representing the first control point of the Bezier curve
     */
    QPoint first() const;
    /*!
     * \brief Returns the last control point of the Bezier curve
     * \return A QPoint representing the last control point of the Bezier curve
     */
    QPoint last() const;
    /*!
     * \brief Returns the current point on the Bezier curve
     * \return A QPoint representing the current point on the Bezier curve
     */
    QPoint current() const;
    /*!
     * \brief Moves to the next point on the Bezier curve and returns it
     * \return A QPoint representing the next point on the Bezier curve
     */
    QPoint next();

  private:
    /*!
     * \brief The size of the scene
     */
    const QSize m_size = QSize(800, 800);
    /*!
     * \brief The color of the curve line
     */
    const QColor m_lineColor = QColor(0, 0, 0);
    /*!
     * \brief The color of the control points
     */
    const QColor m_pointColor = QColor(0, 0, 255);
    /*!
     * \brief The color of the selected control point
     */
    const QColor m_selectColor = QColor(255, 0, 0);
    /*!
     * \brief The margin for the control point selection
     */
    const int m_margin = 10;
    /*!
     * \brief The width of the curve line
     */
    const int m_lineWidth = 1;
    /*!
     * \brief The width of the control points
     */
    const int m_pointWidth = 7;
    /*!
     * \brief The Pascal's triangle used for the curve calculation
     */
    PascalTriangle m_triangle;
    /*!
     * \brief The control points of the Bezier curve
     */
    QList<QPoint> m_controlPoints;
    /*!
     * \brief The points on the Bezier curve
     */
    QList<QPoint> m_points;
    /*!
     * \brief The number of control points for the curve
     */
    int m_cpCount;
    /*!
     * \brief The index of the selected control point
     */
    int m_selectIdx;
    /*!
     * \brief The current index on the Bezier curve
     */
    int m_i;
    /*!
     * \brief The direction of the current index on the Bezier curve (either 1 or -1)
     */
    int m_di;
    /*!
     * \brief Calculates the Bezier curve
     */
    void calculateCurve();
    /*!
     * \brief Returns the number of points to be generated based on the span of the curve
     * \return An integer representing the number of points
     */
    int getCount() const;
    /*!
     * \brief Paints the curve of the Bezier curve
     * \param painter The QPainter object used for painting
     */
    void paintCurve(QPainter &painter) const;
    /*!
     * \brief Paints the polyline of the Bezier curve
     * \param painter The QPainter object used for painting
     */
    void paintPolyline(QPainter &painter) const;
    /*!
     * \brief Compares two points
     * \param x1 The x-coordinate of the first point
     * \param y1 The y-coordinate of the first point
     * \param x2 The x-coordinate of the second point
     * \param y2 The y-coordinate of the second point
     * \return A boolean indicating whether the two points are close enough (within margin)
     */
    inline bool compare(const int& x1, const int& y1, const int& x2, const int& y2)
    {
        if (qFabs(x1 - x2) <= m_margin && qFabs(y1 - y2) <= m_margin) { return true; }
        return false;
    }
};
