#include "ClosestPair2D.h"

#include <sstream>
#include <algorithm>
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
  PointIndexes  pointIndexesLeft;
  PointIndexes  pointIndexesRight;
  vector<Value> xs;

  Select      select;
  Value       xMedian;
  SolveResult resultLeft;
  SolveResult resultRight;
  SolveResult resultMerge;

  /*
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
  */

  return resultMerge;
}
// end private member functions
