#pragma once

#include <QList>

class Circle
{
  public:
    explicit Circle(int count = 120);
    float current() const;
    float next();

  private:
    int m_i;
    int m_count;
    QList<float> m_degrees;
};
