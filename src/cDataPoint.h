#pragma once
#include <sstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <memory>

/// Data row with variable number of columns
struct cDataPoint
{
    int myDim;
    std::vector< double > d;

    /** CTOR
        @param[in] dim number of dimensions ( columns ) in the data, default 3
    */
    cDataPoint( int dim = 3 ) : myDim( dim ), d(dim) {}

    /** CTOR
        @param[in] vd vector of values
        The dimensionality will be set to the length of vd
    */
    cDataPoint(const std::vector< double >& vd )
        : cDataPoint( vd.size() )
    {
        for( int k = 0; k < myDim; k++ )
            d[k] = vd[k];
    }

    /// Add
    cDataPoint operator + ( cDataPoint b );

    /// Subtract
    cDataPoint operator - (cDataPoint b);

    /// Divide by scalar
    cDataPoint operator / ( double s );

    /** Sum distance to other data points
        @param[in] locs the other data points
        @return total distance
    */
    double sum_all_distances(
        const std::vector<cDataPoint>& locs ) const;

    /// Distance between data points.
    static double dist(
        const cDataPoint& ra,
        const cDataPoint& rb );

    /// Human readable string to display data
    std::string text() const;
};

typedef std::shared_ptr< cDataPoint > dp_t;



