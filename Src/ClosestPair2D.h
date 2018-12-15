#ifndef CLOSEST_PAIR_H
#define CLOSEST_PAIR_H

#include <vector>
#include <string>
#include <utility>

#include "Point.h"

class ClosestPair2D
{
  public:

    using Value = long;

    inline void setPointNum ( int num );
    inline void addPoint    ( const Value &x, const Value &y );

    void        solve ();
    std::string result();

  private:

    using PointPair     = std::pair<size_t,size_t>;
    using PointIndexes  = std::vector<size_t>;

    struct SolveResult
    {
      Value                   distanceSquare;
      std::vector<PointPair>  pairs;
    };

    SolveResult solve       ( const PointIndexes  &pointIndexes );
    SolveResult solveSameX  ( const PointIndexes  &pointIndexes );
    SolveResult betterResult( SolveResult         resultCurrent, PointPair pointPair );

    std::vector<Point<Value>> mPoints;

    Value mDistanceSquare;

    std::vector<PointPair> mPairs;
};

// public inline member functions
inline void ClosestPair2D::setPointNum ( int num )
{ mPoints.reserve( num ); }
inline void ClosestPair2D::addPoint    ( const Value &x, const Value &y )
{ mPoints.push_back( Point<Value>{ x, y } ); }
// end public inline member functions

#endif
