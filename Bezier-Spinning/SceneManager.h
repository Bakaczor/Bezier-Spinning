#pragma once

#include <QIntValidator>
#include <QMessageBox>
#include <QFileDialog>

#include "BezierCurve.h"
#include "Circle.h"
#include "Enums.h"

class SceneManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isDragging READ isDragging WRITE setIsDragging NOTIFY isDraggingChanged)
    Q_PROPERTY(bool isPolylineVisible READ isPolylineVisible WRITE setIsPolylineVisible NOTIFY isPolylineVisibleChanged)
    Q_PROPERTY(bool isPlaying READ isPlaying WRITE setIsPlaying NOTIFY isPlayingChanged)
    Q_PROPERTY(Algorithm::Enum algorithm READ algorithm WRITE setAlgorithm NOTIFY algorithmChanged)
    Q_PROPERTY(Animation::Enum animation READ animation WRITE setAnimation NOTIFY animationChanged)
  public:
    QSharedPointer<QImage> scene;
    QSharedPointer<QImage> image;

    /*!
     * \brief Constructs a SceneManager object
     * \param parent A pointer to the parent QObject.
     * \param app A pointer to the QApplication.
     */
    explicit SceneManager(QObject* parent = nullptr, QApplication* app = nullptr);

    void paint();
    void play();

    bool isDragging() const;
    void setIsDragging(bool newIsDragging);

    bool isPlaying() const;
    void setIsPlaying(bool newIsPlaying);

    bool isPolylineVisible() const;
    void setIsPolylineVisible(bool newIsPolylineVisible);

    Algorithm::Enum algorithm() const;
    void setAlgorithm(const Algorithm::Enum& newAlgorithm);

    Animation::Enum animation() const;
    void setAnimation(const Animation::Enum& newAnimation);

  public slots:
    void checkPoints(int x, int y);
    void startDragging();
    void stopDragging();
    void movePoint(int x, int y);
    void generate(QString count);
    void load();

  signals:
    void sceneChanged();
    void imageChanged();

    void isDraggingChanged();
    void isPlayingChanged();
    void isPolylineVisibleChanged();
    void algorithmChanged();
    void animationChanged();

  private:
    const QIntValidator m_intValidator = QIntValidator(3, 20, this);
    const QColor m_white = QColor(255, 255, 255);
    const QSize m_sceneSize = QSize(800, 800);
    const QSize m_imageSize = QSize(150, 150);
    const int m_maxPoints = 20;

    QApplication* m_app;

    QPainter m_painter;
    BezierCurve m_curve;
    Circle m_circle;

    bool m_isDragging;
    bool m_isPlaying;
    bool m_isPolylineVisible;
    bool m_loaded;
    Algorithm::Enum m_algorithm;
    Animation::Enum m_animation;

    inline QRect getRect(const int& x, const int& y) const
    {
        return QRect(QPoint(x - m_imageSize.width(), y - m_imageSize.height()),
                     QPoint(x + m_imageSize.width(), y + m_imageSize.height()));
    }
    void draw(const QPoint& p, const float& theta);
};
