#pragma once

#include <QList>

class PascalTriangle
{
  public:
    explicit PascalTriangle(int levels);
    const QList<int>& getRow(int n) const;

  private:
    QList<QList<int>> m_triangle;

};
