#include "ImageProvider.h"

ImageProvider::ImageProvider(QSharedPointer<QImage> image) : QQuickImageProvider(QQuickImageProvider::Image), m_image(image) {}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id)
    Q_UNUSED(size)
    Q_UNUSED(requestedSize)
    return *m_image;
}
