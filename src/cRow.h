#pragma once
#include <sstream>
#include <cmath>
#include <algorithm>
#include <vector>

/// Data row with variable number of columns
struct cRow
{
    int myDim;
    std::vector< double > d;

    /** CTOR
        @param[in] dim number of dimensions ( columns ) in the data, default 3
    */
    cRow( int dim = 3 ) : myDim( dim ), d(dim) {}

    /** CTOR
        @param[in] vd vector of values
        The dimensionality will be set to the length of vd
    */
    cRow(const std::vector< double >& vd )
        : cRow( vd.size() )
    {
        for( int k = 0; k < myDim; k++ )
            d[k] = vd[k];
    }

    /// Add row
    cRow operator + ( cRow b )
    {
        cRow r( myDim );
        std::transform(
            d.begin(), d.end(), b.d.begin(), r.d.begin(),
            []( double a, double b)
        {
            return a+b;
        } );
        return r;
    }

    /// Subtract row
    cRow operator - (cRow b)
    {
        cRow r( myDim );
        std::transform(
            d.begin(), d.end(), b.d.begin(), r.d.begin(),
            []( double a, double b)
        {
            return a-b;
        } );
        return r;
    }
    /// Divide row by scalar
    cRow operator / ( double s )
    {
        if( std::fabs(s) < 0.00000001 )
            throw std::runtime_error("cRow divide by zero");

        cRow r( myDim );
        std::transform(
            d.begin(), d.end(), r.d.begin(),
            [&s]( double a )
        {
            return a / s;
        } );
        return r;

    }



    /** Sum dirtance to other rows
        @param[in] locs the other rows
        @return total distance
    */
    double sum_all_distances( std::vector<cRow>& locs );

    /// Human readable string to display data
    std::string Text() const
    {
        std::stringstream ss;
        for( int k = 0; k < myDim; k++ )
            ss << d[k] << " ";
        return ss.str();
    }
};

/// Pythagonal distance between rows.
double dist( const cRow& ra, const cRow& rb );


