#ifndef POINT_H
#define POINT_H

#include <cmath>

struct Point
{
  long x;
  long y;
}

inline long distance( const Point &a, const Point &b )
{
  return std::sqrt( std::pow( a.x - b.x, 2 ) + std::pow( a.y - b.y, 2 ) );
}

#endif
