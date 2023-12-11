#include <QMatrix2x2>
#include <QVector3D>
#include <QPainter>
#include <QtMath>
#include <QRect>

#include "Algorithms.h"

void Naive(QImage& dest, const QSharedPointer<QImage>& sour, const float& theta, const int& offset)
{
    QImage temp = Sour2Dest(dest.size(), *sour, offset);
    const QSize& size = dest.size();
    const float sin = qSin(theta);
    const float cos = qCos(theta);

    // can be parallelized
    for (int x = 0; x < size.width(); x++)
    {
        for (int y = 0; y < size.height(); y++)
        {
            int X = x - sour->width();
            int Y = y - sour->height();
            float sx = cos * X + sin * Y;
            float sy = cos * Y - sin * X;
            X = sx + sour->width();
            Y = sy + sour->height();
            if (X >= 0 && X < size.width() && Y >= 0 && Y < size.height())
            {
                dest.setPixelColor(x, y, temp.pixelColor(X, Y));
            }
            else
            {
                dest.setPixelColor(x, y, QColor(0, 0, 0, 0));
            }
        }
    }
}

void Shear(QImage& dest, const QSharedPointer<QImage>& sour, const float& theta, const int& offset)
{
    QImage temp = Sour2Dest(dest.size(), *sour, offset);

    float phi = theta;
    if (theta >= 3 * M_PI / 2) {
        phi = theta - 3 * M_PI / 2;
        TurnImage_270(dest, temp);
    }
    else if (theta >= M_PI)
    {
        phi = theta - M_PI;
        TurnImage_180(dest, temp);
    }
    else if (theta >= M_PI / 2)
    {
        phi = theta - M_PI / 2;
        TurnImage_90(dest, temp);
    }
    dest = temp;

    const float sin = qSin(phi);
    const float tan = -qTan(phi / 2);

    ShearX(dest, temp, tan);
    ShearY(temp, dest, sin);
    ShearX(dest, temp, tan);
}

// any outer loop can be parallelized

void ShearX(QImage& dest, QImage& sour, const float& lamda)
{
    const QSize& size = dest.size();
    dest.fill(QColor(0, 0, 0, 0));
    for (int y = 0; y < size.height(); y++)
    {
        const float ly = lamda * (y - sour.height() / 2);
        const int dx = qFloor(ly);
        const float f = ly - dx;

        QColor righCol = sour.pixelColor(0, y);
        for (int x = 0; x < size.width() - 1; x++)
        {
            const int newX = x + dx;
            if (newX < 0 || newX >= size.width()) { continue; }
            const QColor currCol = righCol;
            righCol = sour.pixelColor(x + 1, y);

            QColor sum;
            if (currCol.alpha() == 0 && righCol.alpha() == 0)
            {
                sum = QColor(0, 0, 0, 0);
            }
            else if (currCol.alpha() == 0)
            {
                sum = righCol;
            }
            else if (righCol.alpha() == 0)
            {
                sum = currCol;
            }
            else
            {
                QVector3D curr = (1.0f - f) * QVector3D(currCol.red(), currCol.green(), currCol.blue());
                QVector3D righ = f * QVector3D(righCol.red(), righCol.green(), righCol.blue());
                sum = QColor(curr.x() + righ.x(), curr.y() + righ.y(), curr.z() + righ.z());
            }
            dest.setPixelColor(newX, y, sum);
        }
        const int newX = dx + size.width() - 1;
        if (newX >= 0 && newX < size.width())
        {
            dest.setPixelColor(newX, y, sour.pixelColor(size.width() - 1, y));
        }
    }
}

void ShearY(QImage& dest, QImage& sour, const float& lamda)
{
    const QSize& size = dest.size();
    dest.fill(QColor(0, 0, 0, 0));
    for (int x = 0; x < size.width(); x++)
    {
        const float lx = lamda * (x - sour.width() / 2);
        const int dy = qFloor(lx);
        const float f = lx - dy;

        QColor downCol = sour.pixelColor(x, 0);
        for (int y = 0; y < size.height() - 1; y++)
        {
            const int newY = y + dy;
            if (newY < 0 || newY >= size.height()) { continue; }
            const QColor currCol = downCol;
            downCol = sour.pixelColor(x, y + 1);

            QColor sum;
            if (currCol.alpha() == 0 && downCol.alpha() == 0)
            {
                sum = QColor(0, 0, 0, 0);
            }
            else if (currCol.alpha() == 0)
            {
                sum = downCol;
            }
            else if (downCol.alpha() == 0)
            {
                sum = currCol;
            }
            else
            {
                QVector3D curr = (1.0f - f) * QVector3D(currCol.red(), currCol.green(), currCol.blue());
                QVector3D down = f * QVector3D(downCol.red(), downCol.green(), downCol.blue());
                sum = QColor(curr.x() + down.x(), curr.y() + down.y(), curr.z() + down.z());
            }
            dest.setPixelColor(x, newY, sum);
        }
        const int newY = dy + size.height() - 1;
        if (newY >= 0 && newY < size.height())
        {
            dest.setPixelColor(x, newY, sour.pixelColor(x, size.height() - 1));
        }
    }
}

void TurnImage_90(QImage& dest, QImage& sour)
{
    const QSize& destSize = dest.size();
    for (int x = 0; x < destSize.width(); x++)
    {
        for (int y = 0; y < destSize.height(); y++)
        {
            dest.setPixelColor(x, y, sour.pixelColor(x, sour.height() - 1 - y));
        }
    }
    for (int x = 0; x < destSize.width(); x++)
    {
        for (int y = 0; y < destSize.height(); y++)
        {
            sour.setPixelColor(x, y, dest.pixelColor(y, x));
        }
    }
}

void TurnImage_180(QImage& dest, QImage& sour)
{
    const QSize& destSize = dest.size();
    for (int x = 0; x < destSize.width(); x++)
    {
        for (int y = 0; y < destSize.height(); y++)
        {
            dest.setPixelColor(x, y, sour.pixelColor(x, sour.height() - 1 - y));

        }
    }
    for (int x = 0; x < destSize.width(); x++)
    {
        for (int y = 0; y < destSize.height(); y++)
        {
            sour.setPixelColor(x, y, dest.pixelColor(dest.width() - 1 - x, y));
        }
    }
}

void TurnImage_270(QImage& dest, QImage& sour)
{
    const QSize& destSize = dest.size();
    for (int x = 0; x < destSize.width(); x++)
    {
        for (int y = 0; y < destSize.height(); y++)
        {
            dest.setPixelColor(x, y, sour.pixelColor(y, x));
        }
    }
    for (int x = 0; x < destSize.width(); x++)
    {
        for (int y = 0; y < destSize.height(); y++)
        {
            sour.setPixelColor(x, y, dest.pixelColor(x, dest.height() - 1 - y));
        }
    }
}

QImage Sour2Dest(const QSize& size, const QImage& sour, const int& offset)
{
    QImage temp(size, QImage::Format_ARGB32);
    temp.fill(QColor(0, 0, 0, 0));
    QPainter painter(&temp);
    painter.drawImage(QRect(
                          QPoint(offset, offset),
                          QPoint(size.width() - offset, size.height() - offset)),
                      sour);
    return temp;
}
