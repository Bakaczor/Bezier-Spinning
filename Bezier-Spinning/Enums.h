#pragma once

#include <QObject>

/*!
 * \brief The Algorithm class
 * This class represents an algorithm type for image transformations.
 * It includes two algorithms: Naive and Shear.
 */
class Algorithm : public QObject
{
    Q_OBJECT
  public:
    /*!
     * \enum Enum
     * \brief The enumeration of algorithms.
     */
    enum class Enum { Naive, Shear };
    Q_ENUM(Enum)
};

/*!
 * \brief The Animation class
 * This class represents a type of animation for image transformations.
 * It includes two animations: Rotation and Moving.
 */
class Animation : public QObject
{
    Q_OBJECT
  public:
    /*!
     * \enum Enum
     * \brief The enumeration of animations.
     */
    enum class Enum { Rotation, Moving };
    Q_ENUM(Enum)
};
