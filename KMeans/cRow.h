#include <algorithm>

/// Data row
struct cRow
{
    int myDim;
    std::vector< double > d;

    /** CTOR
        @param[in] dim number of dimensions ( columns ) in the data, default 3
    */
    cRow( int dim = 3 ) : myDim( dim ), d(dim) {}
    cRow(const std::vector< double >& vd )
    {
        for( int k = 0; k < myDim; k++ )
            d[k] = vd[k];
    }
    cRow operator + ( cRow b )
    {
        cRow r( myDim );
        std::transform( d.begin(), d.end(), b.d.begin(), r.d.begin(),
                        []( double a, double b)
        {
            return a+b;
        } );
        return r;
    }

    cRow operator - (cRow b)
    {
        cRow r( myDim );
        std::transform( d.begin(), d.end(), b.d.begin(), r.d.begin(),
                        []( double a, double b)
        {
            return a-b;
        } );
        return r;
    }
    cRow operator / ( double s )
    {
        if( fabs(s) < 0.00000001 )
            throw std::runtime_error("cRow divide by zero");

        cRow r( myDim );
        std::transform( d.begin(), d.end(), r.d.begin(),
                        [&s]( double a )
        {
            return a / s;
        } );
        return r;

    }
    double dist( const cRow& o )
    {
        //cout << "dist " << Text() << " " << o.Text() << "\n";
        double t = 0;
        cRow r( myDim );
        std::transform( d.begin(), d.end(), o.d.begin(), r.d.begin(),
                        [&t]( double a, double b)
        {
            double delta = a-b;
            t += delta * delta;
            return 0;
        } );

        return sqrt( t );
    }
    double sum_all_distances( const vector<cRow>& locs )
    {
        double total = 0;
        for( auto& l : locs )
        {
            total += dist( l );
        }
        return total;
    }
    string Text() const
    {
        stringstream ss;
        for( int k = 0; k < myDim; k++ )
            ss << d[k] << " ";
        return ss.str();
    }
};

