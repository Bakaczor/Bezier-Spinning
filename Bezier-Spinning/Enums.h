#pragma once

#include <QObject>

class Algorithm : public QObject
{
    Q_OBJECT
  public:
    enum class Enum { Naive, Shear };
    Q_ENUM(Enum)
};


class Animation : public QObject
{
    Q_OBJECT
  public:
    enum class Enum { Rotation, Moving };
    Q_ENUM(Enum)
};

