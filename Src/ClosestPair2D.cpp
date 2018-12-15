#include "ClosestPair2D.h"

#include <sstream>
#include <algorithm>
#include <cassert>
#include <limits>
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
     oss << pointPair.first << " " << pointPair.second << "\n";

  return oss.str();
}
// end public member functions

// private member functions
ClosestPair2D::SolveResult ClosestPair2D::solve( const PointIndexes &pointIndexes )
{
  assert( !pointIndexes.empty() ); // precondition

  SolveResult resultMerge;

  if( pointIndexes.size() <= 2 )
  {
    if( pointIndexes.size() == 1 )
    {
      resultMerge.distanceSquare = numeric_limits<Value>::max();
    }
    else // 2 points
    {
      PointPair pointPair = make_pair( pointIndexes.front(), pointIndexes.back() );

      if( pointPair.first > pointPair.second )
        swap( pointPair.first, pointPair.second );

      resultMerge.distanceSquare = distanceSquare( mPoints[pointPair.first], mPoints[pointPair.second] );
      resultMerge.pairs.push_back( pointPair );
    }
    return resultMerge;
  }

  PointIndexes  pointIndexesLeft;
  PointIndexes  pointIndexesRight;
  vector<Value> xs;

  Select      select;
  Value       xMedian;
  SolveResult resultLeft;
  SolveResult resultRight;
  Value       distance;

  for( size_t i : pointIndexes )
     xs.push_back( mPoints[i].x );

  xMedian = select.select( xs, xs.size() / 2 + 1 );

  for( size_t i : pointIndexes )
  {
     if( mPoints[i].x < xMedian ) pointIndexesLeft.push_back  ( i );
     else                         pointIndexesRight.push_back ( i );
  }

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

     for( ; j > 0 ; --j )
     {
        const Point<Value> &pRight = mPoints[pointIndexesRight[j]];

        if( pRight.y - pLeft.y > distance ) break;
     }

     for( ; j < pointIndexesRight.size() ; ++j )
     {
        const Point<Value> &pRight = mPoints[pointIndexesRight[j]];

        if( pRight.y - pLeft.y > distance ) continue;
        if( pLeft.y - pRight.y > distance ) break;

        Value distanceS = distanceSquare( pLeft, pRight );

        if( resultMerge.distanceSquare < distanceS  ) continue;

        PointPair pointPair = make_pair( pointIndexesLeft[i], pointIndexesRight[j] );

        if( pointPair.first > pointPair.second )
          swap( pointPair.first, pointPair.second );

        if( resultMerge.distanceSquare > distanceS )
        {
          resultMerge.distanceSquare = distanceS;
          resultMerge.pairs.resize( 1 );
          resultMerge.pairs.front() = pointPair;
        }
        else // equal
        {
          resultMerge.pairs.push_back( pointPair );
        }
     }
  }
  return resultMerge;
}
// end private member functions
