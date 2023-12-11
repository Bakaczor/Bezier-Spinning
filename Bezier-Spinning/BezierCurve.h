#pragma once

#include <QPainter>
#include <QColor>
#include <QPoint>
#include <QSize>
#include <QtMath>

#include "PascalTriangle.h"

class BezierCurve
{
  public:
    explicit BezierCurve(PascalTriangle triangle, int count = 3);

    void generate(int count);
    void select(const int& x, const int& y);
    void drag(const int& x, const int& y);
    void paint(QPainter& painter, const bool& drawPolyline) const;
    float currentAngle() const;
    QPoint first() const;
    QPoint last() const;
    QPoint current() const;
    QPoint next();

  private:
    const QSize m_size = QSize(800, 800);
    const QColor m_lineColor = QColor(0, 0, 0);
    const QColor m_pointColor = QColor(0, 0, 255);
    const QColor m_selectColor = QColor(255, 0, 0);
    const int m_margin = 10;
    const int m_lineWidth = 1;
    const int m_pointWidth = 7;

    PascalTriangle m_triangle;

    QList<QPoint> m_controlPoints;
    QList<QPoint> m_points;
    int m_cpCount;
    int m_selectIdx;
    int m_i;
    int m_di;

    void calculateCurve();

    int getCount() const;
    void paintCurve(QPainter &painter) const;
    void paintPolyline(QPainter &painter) const;

    inline bool compare(const int& x1, const int& y1, const int& x2, const int& y2)
    {
        if (qFabs(x1 - x2) <= m_margin && qFabs(y1 - y2) <= m_margin) { return true; }
        return false;
    }
};
