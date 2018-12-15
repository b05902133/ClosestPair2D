#include "ClosestPair2D.h"

#include <sstream>
using namespace std;

// public member functions
void ClosestPair2D::solve()
{
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
