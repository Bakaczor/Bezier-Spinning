#pragma once

#include <QSharedPointer>
#include <QImage>

/*!
 * \brief Performs a naive rotation on image.
 * \param dest The destination image.
 * \param sour The source image.
 * \param theta The rotation angle in radians.
 * \param offset The offset for the rotation.
 */
void Naive(QImage& dest, const QSharedPointer<QImage>& sour, const float& theta, const int& offset);
/*!
 * \brief Performs a triple shear rotation on image.
 * \param dest The destination image.
 * \param sour The source image.
 * \param theta The rotation angle in radians.
 * \param offset The offset for the rotation.
 */
void Shear(QImage& dest, const QSharedPointer<QImage>& sour, const float& theta, const int& offset);
/*!
 * \brief Performs a shear transformation along the x-axis on image.
 * \param dest The destination image.
 * \param sour The source image.
 * \param lambda The shear factor.
 * \param ys The y-coordinates of the image.
 */
void ShearX(QImage& dest, QImage& sour, const float& lambda, const std::vector<int>& ys);
/*!
 * \brief Performs a shear transformation along the y-axis on image.
 * \param dest The destination image.
 * \param sour The source image.
 * \param lambda The shear factor.
 * \param xs The x-coordinates of the image.
 */
void ShearY(QImage& dest, QImage& sour, const float& lambda, const std::vector<int>& xs);
/*!
 * \brief Rotates an image by 90 degrees.
 * \param dest The destination image.
 * \param sour The source image.
 * \param xs The x-coordinates of the image.
 */
void TurnImage_90(QImage& dest, QImage& sour, const std::vector<int>& xs);
/*!
 * \brief Rotates an image by 180 degrees.
 * \param dest The destination image.
 * \param sour The source image.
 * \param xs The x-coordinates of the image.
 */
void TurnImage_180(QImage& dest, QImage& sour, const std::vector<int>& xs);
/*!
 * \brief Rotates an image by 270 degrees.
 * \param dest The destination image.
 * \param sour The source image.
 * \param xs The x-coordinates of the image.
 */
void TurnImage_270(QImage& dest, QImage& sour, const std::vector<int>& xs);
/*!
 * \brief Places a source image in the center of larger destination image.
 * \param size The size of the destination image.
 * \param sour The source image.
 * \param offset The offset for the conversion.
 * \return The destination image.
 */
QImage Sour2Dest(const QSize& size, const QImage& sour, const int& offset);
