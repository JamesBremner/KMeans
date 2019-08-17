/// 3D point
struct cP
{
    double x, y, z;

    cP() : x(0), y(0), z(0) {}
    cP(double x, double y, double z ) : x(x), y(y), z(z) {}
    cP operator + ( cP b )
    {
        return cP(x + b.x, y + b.y, z + b.z);
    }

    cP operator - (cP b)
    {
        return cP( x - b.x, y - b.y, z - b.z);
    }
    cP operator / ( double s )
    {
        if( fabs(s) < 0.00000001 )
            throw std::runtime_error("cP divide by zero");
        return cP( x / s, y / s, z / s );
    }
    double dist( const cP& o )
    {
        //cout << "dist " << Text() << " " << o.Text() << "\n";
        double dx = x - o.x;
        double dy = y - o.y;
        double dz = z - o.z;
        return sqrt( dx*dx+dy*dy+dz*dz );
    }
    double sum_all_distances( const vector<cP>& locs )
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
        ss << x <<" "<< y <<" "<< z;
        return ss.str();
    }
};

