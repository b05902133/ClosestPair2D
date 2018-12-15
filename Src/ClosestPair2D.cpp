#include "ClosestPair2D.h"

#include <sstream>
#include <algorithm>
#include <cassert>
#include <limits>
#include <iostream>
using namespace std;

#include "Select.h"

// public member functions
void ClosestPair2D::solve()
{
  PointIndexes  pointIndexes;
  SolveResult   resultFinal;

  for( size_t i = 0 ; i < mPoints.size() ; ++i )
     pointIndexes.push_back( i );

  sort( pointIndexes.begin(), pointIndexes.end(),
        [&]( size_t front, size_t back )
        {
          return ( mPoints[front].y > mPoints[back].y );
        } );

  resultFinal     = solve( pointIndexes );
  mDistanceSquare = resultFinal.distanceSquare;
  mPairs          = resultFinal.pairs;

  sort( mPairs.begin(), mPairs.end(),
        []( const PointPair &front, const PointPair &back )
        {
          if( front.first == back.first )
            return ( front.second < back.second );
          return ( front.first < back.first );
        } );
}

std::string ClosestPair2D::result()
{
  ostringstream oss;

  oss << mDistanceSquare << " " << mPairs.size() << "\n";

  for( const PointPair &pointPair : mPairs )
     oss << pointPair.first + 1 << " " << pointPair.second + 1 << "\n";

  return oss.str();
}
// end public member functions

// private member functions
ClosestPair2D::SolveResult ClosestPair2D::solve( const PointIndexes &pointIndexes )
{
  if( pointIndexes.size() <= 1 ) return SolveResult{ numeric_limits<Value>::max(), {} };

  PointIndexes  pointIndexesLeft;
  PointIndexes  pointIndexesRight;
  vector<Value> xs;

  //Select      select;
  Value       xMedian;
  SolveResult resultMerge;
  SolveResult resultLeft;
  SolveResult resultRight;
  Value       distance;

  for( size_t i : pointIndexes )
     xs.push_back( mPoints[i].x );

  sort( xs.begin(), xs.end() );

  xMedian = xs[xs.size()/2+1]; // select.select( xs, xs.size() / 2 + 1 );

  for( size_t i : pointIndexes )
  {
     if( mPoints[i].x < xMedian ) pointIndexesLeft.push_back  ( i );
     else                         pointIndexesRight.push_back ( i );
  }

  if( pointIndexesLeft.empty() || pointIndexesRight.empty() )
    return solveSameX( pointIndexes );

  resultLeft  = solve( pointIndexesLeft   );
  resultRight = solve( pointIndexesRight  );

  if( resultLeft.distanceSquare == resultRight.distanceSquare )
  {
    resultMerge = resultLeft;
    resultMerge.pairs.insert( resultMerge.pairs.end(), resultRight.pairs.begin(), resultRight.pairs.end() );
  }
  else
    resultMerge = ( resultLeft.distanceSquare < resultRight.distanceSquare ) ? resultLeft: resultRight;

  distance = sqrt( resultMerge.distanceSquare );

  for( size_t i = 0, j = 0 ; i < pointIndexesLeft.size() ; ++i )
  {
     const Point<Value> &pLeft = mPoints[pointIndexesLeft[i]];

     if( xMedian - pLeft.x > distance ) continue;

     // find backward to the first point above a ditance **distance**
     for( ; j > 0 ; --j )
     {
        if( j >= pointIndexesRight.size() ) continue;

        const Point<Value> &pRight = mPoints[pointIndexesRight[j]];

        if( pRight.y - pLeft.y > distance ) break;
     }
     // end find backward to the first point above a ditance **distance**

     for( ; j < pointIndexesRight.size() ; ++j )
     {
        const Point<Value> &pRight = mPoints[pointIndexesRight[j]];

        if( pRight.x - xMedian > distance ) continue;
        if( pRight.y - pLeft.y > distance ) continue;
        if( pLeft.y - pRight.y > distance ) break;

        resultMerge = betterResult( resultMerge, make_pair( pointIndexesLeft[i], pointIndexesRight[j] ) );
     }
  }
  return resultMerge;
}

ClosestPair2D::SolveResult ClosestPair2D::solveSameX( const PointIndexes &pointIndexes )
{
  SolveResult resultSameX = { numeric_limits<Value>::max(), {} };

  for( size_t i = 0 ; i < pointIndexes.size() - 1 ; ++i )
  {
     size_t indexA = pointIndexes[i];
     size_t indexB = pointIndexes[i+1];

     resultSameX = betterResult( resultSameX, make_pair( indexA, indexB ) );
  }
  return resultSameX;
}

ClosestPair2D::SolveResult ClosestPair2D::betterResult( SolveResult resultCurrent, PointPair pointPair )
{
  Value distanceS = distanceSquare( mPoints[pointPair.first], mPoints[pointPair.second] );

  if( resultCurrent.distanceSquare < distanceS  ) return resultCurrent;

  if( pointPair.first > pointPair.second )
    swap( pointPair.first, pointPair.second );

  if( resultCurrent.distanceSquare > distanceS )
  {
    resultCurrent.distanceSquare  = distanceS;
    resultCurrent.pairs           = { pointPair };
  }
  else // equal
    resultCurrent.pairs.push_back( pointPair );

  return resultCurrent;
}
// end private member functions
