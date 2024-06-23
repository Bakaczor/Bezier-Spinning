#include <QtConcurrent/QtConcurrent>
#include <QRandomGenerator>
#include <QVector2D>
#include <iterator>

#include "BezierCurve.h"

BezierCurve::BezierCurve(PascalTriangle triangle, int count) : m_triangle(triangle), m_i(0), m_di(1)
{
    generate(count);
}

void BezierCurve::generate(int count)
{
    m_controlPoints.clear();
    m_points.clear();

    m_cpCount = count;
    m_selectIdx = -1;

    m_controlPoints = QList<QPoint>(m_cpCount);
    QtConcurrent::blockingMap(m_controlPoints, [this](const QPoint& p) {
        std::ptrdiff_t i = std::distance(&m_controlPoints.at(0), &p);
        int x = QRandomGenerator::global()->bounded(0, m_size.width());
        int y = QRandomGenerator::global()->bounded(0, m_size.height());
        m_controlPoints[i] = QPoint(x, y);
    });

    calculateCurve();
    if (m_i > m_points.count() - 1)
    {
        m_i = m_points.count() - 1;
    }
    getCount();
}

void BezierCurve::select(const int& x, const int& y)
{
    m_selectIdx = -1;
    QtConcurrent::blockingMap(m_controlPoints, [this, &x, &y](const QPoint& p) {
        std::ptrdiff_t i = std::distance(&m_controlPoints.at(0), &p);
        if (compare(x, y, p.x(), p.y()))
        {
            m_selectIdx = i;
        }
    });
}

void BezierCurve::drag(const int& x, const int& y)
{
    if (m_selectIdx != -1)
    {
        m_controlPoints[m_selectIdx] = QPoint(x, y);
        m_points.clear();
        calculateCurve();
        if (m_i > m_points.count() - 1)
        {
            m_i = m_points.count() - 1;
        }
    }
}

void BezierCurve::paint(QPainter& painter, const bool& drawPolyline) const
{
    paintCurve(painter);
    if (drawPolyline)
    {
        paintPolyline(painter);
    }
}

float BezierCurve::currentAngle() const
{
    const int n = m_cpCount - 2;
    const QList<int> &row = m_triangle.getRow(n);
    const auto dB = [&row, &n](const int &i, const float &t) -> float {
        return row.at(i) * qPow(t, i) * qPow(1 - t, n - i);
    };

    const float t = static_cast<float>(m_i) / m_points.count();

    float X = 0.0f;
    float Y = 0.0f;
    for (int j = 0; j <= n; j++)
    {
        const float res = dB(j, t);
        X += (m_controlPoints.at(j + 1).x() - m_controlPoints.at(j).x()) * res;
        Y += (m_controlPoints.at(j + 1).y() - m_controlPoints.at(j).y()) * res;
    }
    QVector2D T(X, Y);
    T.normalize();
    if (T.y() >= 0)
    {
        return qAcos(T.x());
    }
    else
    {
        return 2 * M_PI - qAcos(T.x());
    }
}

QPoint BezierCurve::first() const
{
    return m_controlPoints.constFirst();
}

QPoint BezierCurve::last() const
{
    return m_controlPoints.constLast();
}

QPoint BezierCurve::current() const
{
    return m_points.at(m_i);
}

QPoint BezierCurve::next()
{
    if ((m_i == 0 && m_di < 0) || (m_i == m_points.count() - 1 && m_di > 0))
    {
        m_di = -m_di;
    }
    m_i += m_di;
    return current();
}

void BezierCurve::calculateCurve()
{
    const int tCount = getCount();
    const float step = 1.0f / tCount;

    const int n = m_cpCount - 1;
    const QList<int> &row = m_triangle.getRow(n);
    const auto B = [&row, &n](const int &i, const float &t) -> float {
        return row.at(i) * qPow(t, i) * qPow(1 - t, n - i);
    };

    QList<float> ts(tCount);
    ts[0] = 0.0f;
    for (int i = 1; i < tCount; i++)
    {
        ts[i] = ts[i - 1] + step;
    }

    m_points = QList<QPoint>(tCount);
    QtConcurrent::blockingMap(m_points, [this, &ts, &n, &B](const QPoint& p) {
        std::ptrdiff_t i = std::distance(&m_points.at(0), &p);
        const float& t = ts.at(i);
        float X = 0.0f;
        float Y = 0.0f;
        for (int j = 0; j <= n; j++)
        {
            const float res = B(j, t);
            X += m_controlPoints.at(j).x() * res;
            Y += m_controlPoints.at(j).y() * res;
        }
        m_points[i] = QPoint(X, Y);
    });
}

int BezierCurve::getCount() const
{
    int minX = m_controlPoints.constFirst().x();
    int minY = m_controlPoints.constFirst().y();
    int maxX = m_controlPoints.constFirst().x();
    int maxY = m_controlPoints.constFirst().y();

    for (const QPoint& p : m_controlPoints)
    {
        if (p.x() < minX)
        {
            minX = p.x();
        }
        else if (p.x() > maxX)
        {
            maxX = p.x();
        }

        if (p.y() < minY)
        {
            minY = p.y();
        }
        else if (p.y() > maxY)
        {
            maxY = p.y();
        }
    }

    return qMax(maxX - minX, maxY - minY) / 2;
}

void BezierCurve::paintCurve(QPainter& painter) const
{
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(m_lineWidth + 2);
    pen.setColor(m_lineColor);
    painter.setPen(pen);

    for (int i = 0; i < m_points.count() - 1; i++)
    {
        painter.drawLine(m_points.at(i), m_points.at(i + 1));
    }
}

void BezierCurve::paintPolyline(QPainter& painter) const
{
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    for (int i = 0; i < m_controlPoints.count() - 1; i++)
    {
        pen.setWidth(m_lineWidth);
        pen.setColor(m_lineColor);
        painter.setPen(pen);
        painter.drawLine(m_controlPoints.at(i), m_controlPoints.at(i + 1));

        pen.setWidth(m_pointWidth);
        if (i == m_selectIdx)
        {
            pen.setColor(m_selectColor);
        }
        else
        {
            pen.setColor(m_pointColor);
        }
        painter.setPen(pen);
        painter.drawPoint(m_controlPoints.at(i));
    }

    if (m_controlPoints.count() - 1 == m_selectIdx)
    {
        pen.setColor(m_selectColor);
    }
    else
    {
        pen.setColor(m_pointColor);
    }
    painter.setPen(pen);
    painter.drawPoint(m_controlPoints.constLast());
}
