#pragma once

#include <QSharedPointer>
#include <QImage>

void Naive(QImage& dest, const QSharedPointer<QImage>& sour, const float& theta, const int& offset);

void Shear(QImage& dest, const QSharedPointer<QImage>& sour, const float& theta, const int& offset);

void ShearX(QImage& dest, QImage& sour, const float& lamda);

void ShearY(QImage& dest, QImage& sour, const float& lamda);

void TurnImage_90(QImage& dest, QImage& sour);

void TurnImage_180(QImage& dest, QImage& sour);

void TurnImage_270(QImage& dest, QImage& sour);

QImage Sour2Dest(const QSize& size, const QImage& sour, const int& offset);
