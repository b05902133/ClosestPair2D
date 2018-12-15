#ifndef POINT_H
#define POINT_H

#include <cmath>

template<class Value>
struct Point
{
  Value x;
  Value y;
};

template<class Value>
inline Value distance( const Point<Value> &a, const Point<Value> &b )
{
  return std::sqrt( std::pow( a.x - b.x, 2 ) + std::pow( a.y - b.y, 2 ) );
}

#endif
