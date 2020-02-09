
#define PYTHAGORUS

#include <vector>
#include <numeric>
#include "cDataPoint.h"

using namespace std;

    cDataPoint cDataPoint::operator + ( cDataPoint b )
    {
        cDataPoint r( myDim );
        std::transform(
            d.begin(), d.end(), b.d.begin(), r.d.begin(),
            []( double a, double b)
        {
            return a+b;
        } );
        return r;
    }

cDataPoint cDataPoint::operator - (cDataPoint b)
{
    cDataPoint r( myDim );
    std::transform(
        d.begin(), d.end(), b.d.begin(), r.d.begin(),
        []( double a, double b)
    {
        return a-b;
    } );
    return r;
}

cDataPoint cDataPoint::operator / ( double s )
{
    if( std::fabs(s) < 0.00000001 )
        throw std::runtime_error("cDataPoint divide by zero");

    cDataPoint r( myDim );
    std::transform(
        d.begin(), d.end(),
        r.d.begin(),
        [&s]( double a )
    {
        return a / s;
    } );
    return r;
}

double cDataPoint::dist(
    const cDataPoint& ra,
    const cDataPoint& rb )
{
#ifdef PYTHAGORUS
    //cout << "dist " << ra.Text() << " " << rb.Text() << "\n";

    // calculated squared difference between datapoints for each dimension
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

    // return square root of sum of squared differences
    return sqrt(
               accumulate(
                   squared_deltas.begin(),
                   squared_deltas.end(),
                   0 ));

#endif // PYTHAGORUS
}

double cDataPoint::sum_all_distances(
    const std::vector<cDataPoint>& locs ) const
{
    double total = 0;
    for( auto& l : locs )
    {
        total += dist( *this, l );
    }
    return total;
}

std::string cDataPoint::text() const
{
    std::stringstream ss;
    for( int k = 0; k < myDim; k++ )
        ss << d[k] << " ";
    return ss.str();
}


