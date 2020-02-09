#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/variance.hpp>

using namespace std;

#include "cDataPoint.h"
#include "KMeans.h"

void KMeans::Add( const vector<double>& p )
{
    if( myLocations.size() )
    {
        if( myLocations[0]->myDim != p.size() )
        {
            throw std::runtime_error("Inconsistent data attribute count");
        }
    }
    myLocations.push_back( dp_t( new cDataPoint( p ) ) );
}

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

std::string KMeans::text()
{
    stringstream ss;
    int kc = 0;
    for( auto& c : myClusters )
    {
        ss << "Cluster " << kc << " : ";
        for( int k = 0; k < (int)myLocations.size(); k++ )
            if( myAssigns[k] == kc )
                ss << myLocations[k]->text() << ", ";
        ss << "\n" << ClusterStats( kc ) << "\n";
        kc++;
    }
    return ss.str();
}

void KMeans::Assign()
{
    myAssigns.clear();
    for( auto& c : myClusters )
        c.clear();

    for( auto& cl : myLocations )
    {
        //cout << "assigning " << cl.Text() << "\n";
        double m = 1000000000000000000000.0;
        int closest_cluster;
        for( int si = 0; si < myClusterCount; si++ )
        {
            //cout << "test cluster " << myClusters[ si ].text() << "\n";
            double td = myClusters[ si ].dist( cl );
            if( td < m )
            {
                m = td;
                closest_cluster = si;
            }
        }
        myAssigns.push_back( closest_cluster );
        myClusters[ closest_cluster ].add( cl );
    }
}

void KMeans::MoveClustersToMean()
{
    for( int ks = 0; ks < myClusterCount; ks++ )
    {
        cDataPoint A( myLocations[0]->myDim );
        int count = 0;
        for( int kl = 0; kl < (int)myLocations.size(); kl++ )
        {
            if( ks == myAssigns[ kl ] )
            {
                A = A + *myLocations[ kl ].get();
                count++;
            }
        }
        //cout << "cluster " << ks << " has "<< count << " " << A.Text() << "\n";
        if( count )
            myClusters[ ks ].move( A / count );
    }
}

void KMeans::Init(
    int clusterCount,
    bool frandom )
{
    myClusterCount = clusterCount;

    if( myClusterCount > (int)myLocations.size() )
        throw std::runtime_error("KMeans::ClusterCount less locations than clusters");

    if( frandom )
        ClusterLocationInitRandom();
    else
        ClusterLocationInitIndex();
}
void KMeans::ClusterLocationInitIndex()
{
    myClusters.clear();
    for( int k = 0; k < myClusterCount; k++ )
    {
        int ic = k * (double)myLocations.size()/myClusterCount;
        //cout << ic <<" "<< myLocations[ic].Text() << ", ";
        myClusters.push_back( cCluster( *myLocations[ic].get() ) );
    }
}
void KMeans::ClusterLocationInitRandom()
{
    /* initialize random seed: */
    srand (time(NULL));
    myClusters.clear();
    for( int k = 0; k < myClusterCount; k++ )
    {
        myClusters.push_back( *myLocations[ rand() % myLocations.size() ].get() );
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
    ss << myClusters[ cluster ].text();

    typedef boost::accumulators::accumulator_set<double, boost::accumulators::stats<
    boost::accumulators::tag::min,
          boost::accumulators::tag::max,
          boost::accumulators::tag::mean,
          boost::accumulators::tag::variance,
          boost::accumulators::tag::count> >
          Accumulator_t;
    vector< Accumulator_t > vac( myLocations[0]->myDim );


    for( int k = 0; k < (int)myLocations.size(); k++ )
    {
        if( cluster == myAssigns[ k ] )
        {
            for( int kd = 0; kd < (int)myLocations[0]->myDim; kd++ )
            {
                vac[ kd ]( myLocations[k]->d[kd] );
            }
        }
    }

    ss << " mins: ";
    for( int kd = 0; kd < (int)myLocations[0]->myDim; kd++ )
    {
        ss << boost::accumulators::min( vac[kd] ) << ", ";
    }
    ss << " maxs: ";
    for( int kd = 0; kd < (int)myLocations[0]->myDim; kd++ )
    {
        ss << boost::accumulators::max( vac[kd] ) << ", ";
    }
    ss << " sds: ";
    for( int kd = 0; kd < (int)myLocations[0]->myDim; kd++ )
    {
        ss << sqrt(boost::accumulators::variance( vac[kd] )) << ", ";
    }
    ss << "\n";

    return ss.str();
}

std::vector< cCluster >&
KMeans::clusters()
{
    return myClusters;
}

double cCluster::dist( dp_t o )
{
    return cDataPoint::dist( myCenter, *o.get() );
}
std::string cCluster::text() const
{
    return myCenter.text();
}
void cCluster::move( const cDataPoint& r )
{
    myCenter = r;
}
cCluster::cCluster( const cDataPoint& r )
{
    myCenter = r;
}
void cCluster::clear()
{
    myPoints.clear();
}
void cCluster::add( dp_t p )
{
    myPoints.push_back( p );
}
std::vector< dp_t >& cCluster::points()
{
    return myPoints;
}
cDataPoint& cCluster::center()
{
    return myCenter;
}




