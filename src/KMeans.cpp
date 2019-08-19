#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/variance.hpp>

using namespace std;

#include "cRow.h"
#include "KMeans.h"

double KMeans::TotalDistanceToCluster()
{
    double total = 0;
    for( int kc = 0; kc < myClusterCount; kc++ )
    {
        for( int kl = 0; kl < (int)myLocations.size(); kl++ )
        {
            if( myAssigns[kl] == kc )
            {
                // add distance from location to cluster center it is assigned to
                total += myClusters[kc].dist( myLocations[ kl ] );
            }
        }
    }
    return total;
}

std::string KMeans::AssignText()
{
    stringstream ss;
    for( int k = 0; k < (int)myLocations.size(); k++ )
        ss << k << " ( " << myLocations[k].Text()
           << " ) in cluster " << myAssigns[k] <<" ( "
           <<  myClusters[ myAssigns[k] ].Text() <<" )\n";
    return ss.str();
}

void KMeans::Assign()
{
    myAssigns.clear();
    for( auto& cl : myLocations )
    {
        double m = 1000000000000000000000.0;
        int sg;
        for( int si = 0; si < myClusterCount; si++ )
        {
            double td = cl.dist( myClusters[ si ] );
            if( td < m )
            {
                m = td;
                sg = si;
            }
        }
        myAssigns.push_back( sg );
    }
}

void KMeans::MoveClustersToMean()
{
    for( int ks = 0; ks < myClusterCount; ks++ )
    {
        cRow A( myLocations[0].myDim );
        int count = 0;
        for( int kl = 0; kl < (int)myLocations.size(); kl++ )
        {
            if( ks == myAssigns[ kl ] )
            {
                A = A + myLocations[ kl ];
                count++;
            }
        }
        //cout << "cluster " << ks << " has "<< count << " " << A.Text() << "\n";
        if( count )
            myClusters[ ks ] = A / count;
    }
}

void KMeans::ClusterCount( int c )
{
    myClusterCount = c;

    if( myClusterCount > (int)myLocations.size() )
        throw std::runtime_error("KMeans::ClusterCount less locations than clusters");

    // initialize cluster locations among data locations by index
    myClusters.clear();
    for( int k = 0; k < myClusterCount; k++ )
    {
        int ic = k * (double)myLocations.size()/myClusterCount;
        cout << ic <<" "<< myLocations[ic].Text() << ", ";
        myClusters.push_back( myLocations[ic] );
    }
}

void KMeans::Iter( int max )
{
    double dt = 0;

    for( int kiter=0; kiter < max; kiter++ )
    {
        // assign locations to nearest cluster
        Assign();

        // move clusters to mean location of locations assigned
        MoveClustersToMean();

        double d = TotalDistanceToCluster();
        if( fabs( dt - d ) < .000001 )
            break;
    }
}

std::string KMeans::ClusterStats( int cluster )
{
    std::stringstream ss;
    ss << "Cluster " << cluster << " means ";
    if( 0 > cluster || cluster > (int)myClusters.size())
        return ss.str();
    ss << myClusters[ cluster ].Text();

    typedef boost::accumulators::accumulator_set<double, boost::accumulators::stats<
    boost::accumulators::tag::min,
          boost::accumulators::tag::max,
          boost::accumulators::tag::mean,
          boost::accumulators::tag::variance,
          boost::accumulators::tag::count> >
          Accumulator_t;
    vector< Accumulator_t > vac( myLocations[0].myDim );


    for( int k = 0; k < (int)myLocations.size(); k++ )
    {
        if( cluster == myAssigns[ k ] )
        {
            for( int kd = 0; kd < (int)myLocations[0].myDim; kd++ )
            {
                vac[ kd ]( myLocations[k].d[kd] );
            }
        }
    }

    ss << " mins: ";
    for( int kd = 0; kd < (int)myLocations[0].myDim; kd++ )
    {
        ss << boost::accumulators::min( vac[kd] ) << ", ";
    }
    ss << " maxs: ";
    for( int kd = 0; kd < (int)myLocations[0].myDim; kd++ )
    {
        ss << boost::accumulators::max( vac[kd] ) << ", ";
    }
    ss << " sds: ";
    for( int kd = 0; kd < (int)myLocations[0].myDim; kd++ )
    {
        ss << sqrt(boost::accumulators::variance( vac[kd] )) << ", ";
    }
    ss << "\n";

    return ss.str();
}
