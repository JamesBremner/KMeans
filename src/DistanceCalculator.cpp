/** Calculate "distance" between data points.

  Specify distance measure used for next build
  by defining one of PYTHAGORUS, ...
*/

#define PYTHAGORUS

#include "cRow.h"

double dist( const cRow& ra, const cRow& rb )
{
#ifdef PYTHAGORUS
    //cout << "dist " << ra.Text() << " " << rb.Text() << "\n";
    double t = 0;

    // loop over data dimensions
    for( int k = 0; k < ra.myDim; k++ )
    {
        // difference between data points for this dimension
        double delta = ra.d[k] - rb.d[k];

        // accumulate squares of differences
        t += delta * delta;
    }

    // return square of sum of differences squared
    return std::sqrt( t );
#endif // PYTHAGORUS
}
