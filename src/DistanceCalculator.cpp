/** Calculate "distance" between data points.

  Specify distance measure used for next build
  by defining one of PYTHAGORUS, ...
*/

#define PYTHAGORUS

#include <vector>
#include <numeric>
#include "cRow.h"

using namespace std;

double dist( const cRow& ra, const cRow& rb )
{
#ifdef PYTHAGORUS
    //cout << "dist " << ra.Text() << " " << rb.Text() << "\n";
//    double t = 0;
//
//    // loop over data dimensions
//    for( int k = 0; k < ra.myDim; k++ )
//    {
//        // difference between data points for this dimension
//        double delta = ra.d[k] - rb.d[k];
//
//        // accumulate squares of differences
//        t += delta * delta;
//    }
//
//    // return square of sum of differences squared
//    return std::sqrt( t );

    vector< double > squared_deltas( ra.myDim );
    transform(
        ra.d.begin(), ra.d.end(),
        rb.d.begin(),
        squared_deltas.begin(),
        [](double a, double b)
    {
        double delta = a - b;
        return delta * delta;
    });
    return sqrt(
               accumulate(
                   squared_deltas.begin(),
                   squared_deltas.end(),
                   0 ));

#endif // PYTHAGORUS
}
