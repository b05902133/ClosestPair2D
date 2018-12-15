#include <iostream>
using namespace std;

#include "ClosestPair2D.h"

int main()
{
  ClosestPair2D solver;
  int           pointNum;

  cin >> pointNum;

  solver.setPointNum( pointNum );

  for( int i = 0 ; i < pointNum ; ++i )
  {
     ClosestPair2D::Value x, y;

     cin >> x >> y;

     solver.addPoint( x, y );
  }
  solver.solve();

  cout << solver.result() << "\n";

  return 0;
}
