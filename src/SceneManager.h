#pragma once

#include <QIntValidator>
#include <QMessageBox>
#include <QFileDialog>

#include "BezierCurve.h"
#include "Circle.h"
#include "Enums.h"

/*!
 * \brief The SceneManager class
 * This class manages the scene, including the Bezier curve and the image.
 * It provides methods to paint the scene, play the animation, and handle user interactions.
 */
class SceneManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isDragging READ isDragging WRITE setIsDragging NOTIFY isDraggingChanged)
    Q_PROPERTY(bool isPolylineVisible READ isPolylineVisible WRITE setIsPolylineVisible NOTIFY isPolylineVisibleChanged)
    Q_PROPERTY(bool isPlaying READ isPlaying WRITE setIsPlaying NOTIFY isPlayingChanged)
    Q_PROPERTY(Algorithm::Enum algorithm READ algorithm WRITE setAlgorithm NOTIFY algorithmChanged)
    Q_PROPERTY(Animation::Enum animation READ animation WRITE setAnimation NOTIFY animationChanged)
  public:
    /*!
     * \brief An image representing the scene
     */
    QSharedPointer<QImage> scene;
    /*!
     * \brief An image selected by user
     */
    QSharedPointer<QImage> image;
    /*!
     * \brief Constructs a SceneManager object
     * \param parent A pointer to the parent QObject.
     * \param app A pointer to the QApplication.
     */
    explicit SceneManager(QObject* parent = nullptr, QApplication* app = nullptr);
    /*!
     * \brief Paints the scene
     */
    void paint();
    /*!
     * \brief Plays the animation
     */
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
    /*!
     * \brief Selects a control point based on provided coordinates
     * \param x The x-coordinate of the point to check
     * \param y The y-coordinate of the point to check
     */
    void checkPoints(int x, int y);
    /*!
     * \brief Starts dragging
     */
    void startDragging();
    /*!
     * \brief Stops dragging
     */
    void stopDragging();
    /*!
     * \brief Moves the selected points to provided coordinates
     * \param x The x-coordinate of the point to move
     * \param y The y-coordinate of the point to move
     */
    void movePoint(int x, int y);
    /*!
     * \brief Generates a new Bezier curve
     * \param count The number of control points for the curve
     */
    void generate(QString count);
    /*!
     * \brief Loads an image
     */
    void load();

    // new functionality
    void create();

  signals:
    void sceneChanged();
    void imageChanged();

    void isDraggingChanged();
    void isPlayingChanged();
    void isPolylineVisibleChanged();
    void algorithmChanged();
    void animationChanged();

  private:
    /*!
     * \brief The integer validator for the number of points
     */
    const QIntValidator m_intValidator = QIntValidator(3, 20, this);
    /*!
     * \brief The color for the scene background
     */
    const QColor m_white = QColor(255, 255, 255);
    /*!
     * \brief The size of the scene
     */
    const QSize m_sceneSize = QSize(800, 800);
    /*!
     * \brief The size of the image
     */
    const QSize m_imageSize = QSize(150, 150);
    /*!
     * \brief The maximum number of points for the Bezier curve
     */
    const int m_maxPoints = 20;
    /*!
     * \brief The running QApplication
     */
    QApplication* m_app;
    /*!
     * \brief The QPainter for drawing
     */
    QPainter m_painter;
    /*!
     * \brief The Bezier curve
     */
    BezierCurve m_curve;
    /*!
     * \brief The circle for rotation
     */
    Circle m_circle;

    bool m_isDragging;
    bool m_isPlaying;
    bool m_isPolylineVisible;
    bool m_loaded;
    Algorithm::Enum m_algorithm;
    Animation::Enum m_animation;

    /*!
     * \brief Gets the rectangle for drawing
     * \param x The x-coordinate of the point
     * \param y The y-coordinate of the point
     * \return A QRect representing the rectangle for drawing
     */
    inline QRect getRect(const int& x, const int& y) const
    {
        return QRect(QPoint(x - m_imageSize.width(), y - m_imageSize.height()),
                     QPoint(x + m_imageSize.width(), y + m_imageSize.height()));
    }
    /*!
     * \brief Draws the image at given point with a certain rotation angle
     * \param p The point
     * \param theta The angle
     */
    void draw(const QPoint& p, const float& theta);

    // new functionality
    QColor HSV2RGB(const float& hue, const float& saturation, const float& value);
};
