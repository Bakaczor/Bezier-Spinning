#include <QApplication>
#include <QElapsedTimer>
#include <QEventLoop>
#include <QThread>

#include "SceneManager.h"
#include "Algorithms.h"

SceneManager::SceneManager(QObject* parent, QApplication* app) : QObject(parent), m_app(app), m_curve(PascalTriangle(m_maxPoints - 1), 3),
      m_isDragging(false), m_isPolylineVisible(true), m_loaded(false), m_algorithm(Algorithm::Enum::Naive), m_animation(Animation::Enum::Rotation)
{
    image = QSharedPointer<QImage>(new QImage(m_imageSize, QImage::Format_ARGB32));
    scene = QSharedPointer<QImage>(new QImage(m_sceneSize, QImage::Format_ARGB32), [this](QImage* image) {
        // the painter must be freed before freeing the device
        m_painter.end();
        delete image;
    });

    image->fill(m_white);
    scene->fill(m_white);
    m_painter.begin(scene.get());
    m_painter.setRenderHint(QPainter::Antialiasing, true);
    paint();
}

void SceneManager::paint()
{
    scene->fill(m_white);
    m_curve.paint(m_painter, m_isPolylineVisible);
    if (m_loaded)
    {
        if (m_animation == Animation::Enum::Rotation)
        {
            QPoint p = m_curve.current();
            float theta = m_isPlaying ? m_circle.next() : m_circle.current();
            draw(p, theta);
        }
        else
        {
            QPoint p = m_isPlaying ? m_curve.next() : m_curve.current();
            draw(p, m_curve.currentAngle());
        }
    }
}

void SceneManager::play()
{
    const int frame = 30;
    QElapsedTimer timer;
    timer.start();
    while (m_isPlaying)
    {
        timer.restart();
        paint();
        const int remaining = frame - timer.elapsed();
        const int toWait = remaining < 0 ? 0 : remaining;
        QThread::msleep(toWait);
        emit sceneChanged();
        m_app->processEvents(QEventLoop::AllEvents);
    }
}

// === SLOTS ===

void SceneManager::checkPoints(int x, int y)
{
    m_curve.select(x, y);
    paint();
    emit sceneChanged();
}

void SceneManager::movePoint(int x, int y)
{
    m_curve.drag(x, y);
    paint();
    emit sceneChanged();
}

void SceneManager::generate(QString count)
{
    int validated = 0;
    QValidator::State state = m_intValidator.validate(count, validated);
    if (state == QValidator::State::Acceptable)
    {
        validated = count.toInt();
    }
    if (state != QValidator::State::Acceptable || validated < 3 || validated > 20)
    {
        QMessageBox::warning(nullptr, tr("Warning"), tr("The number of the points is invalid.\n"
                                                        "Please enter a number between 3 and 20."));
        return;
    }
    m_curve.generate(validated);
    paint();
    emit sceneChanged();
}

void SceneManager::load()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Open File"), "/home", tr("Images (*.png *.jpg)"));
    if (!fileName.isEmpty())
    {
        image->load(fileName);
        *image = image->scaled(m_imageSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        image->convertTo(QImage::Format_ARGB32);
        m_loaded = true;
    }
    else
    {
        *image = QImage(m_imageSize, QImage::Format_ARGB32);
        image->fill(m_white);
        m_loaded = false;
    }
    emit imageChanged();
    paint();
    emit sceneChanged();
}

void SceneManager::draw(const QPoint& p, const float& theta)
{
    QImage dest(2 * m_imageSize, QImage::Format_ARGB32);
    if (m_algorithm == Algorithm::Enum::Naive)
    {
        Naive(dest, image, theta, m_imageSize.width() / 2);
    }
    else
    {
        Shear(dest, image, theta, m_imageSize.width() / 2);
    }
    QRect rect = getRect(p.x(), p.y());
    m_painter.drawImage(rect, dest);
}

void SceneManager::startDragging()
{
    m_isDragging = true;
}

void SceneManager::stopDragging()
{
    m_isDragging = false;
}

// === PROPERTIES ===

bool SceneManager::isDragging() const
{
    return m_isDragging;
}

void SceneManager::setIsDragging(bool newIsDragging)
{
    if (m_isDragging == newIsDragging) { return; }
    m_isDragging = newIsDragging;
    emit isDraggingChanged();
}

bool SceneManager::isPlaying() const
{
    return m_isPlaying;
}

void SceneManager::setIsPlaying(bool newIsPlaying)
{
    if (m_isPlaying == newIsPlaying) { return; }
    m_isPlaying = newIsPlaying;
    emit isPlayingChanged();
    if (m_isPlaying) { play(); }
}

bool SceneManager::isPolylineVisible() const
{
    return m_isPolylineVisible;
}

void SceneManager::setIsPolylineVisible(bool newIsPolylineVisible)
{
    if (m_isPolylineVisible == newIsPolylineVisible) { return; }
    m_isPolylineVisible = newIsPolylineVisible;
    emit isPolylineVisibleChanged();

    paint();
    emit sceneChanged();
}

Algorithm::Enum SceneManager::algorithm() const
{
    return m_algorithm;
}

void SceneManager::setAlgorithm(const Algorithm::Enum& newAlgorithm)
{
    if (m_algorithm == newAlgorithm) { return; }
    m_algorithm = newAlgorithm;
    emit algorithmChanged();
}

Animation::Enum SceneManager::animation() const
{
    return m_animation;
}

void SceneManager::setAnimation(const Animation::Enum& newAnimation)
{
    if (m_animation == newAnimation) { return; }
    m_animation = newAnimation;
    emit animationChanged();
}


