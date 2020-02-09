#include <vector>

#include "cDataPoint.h"



class cCluster
{
public:
    cCluster( const cDataPoint& r );
    ~cCluster() {}
    double dist( dp_t o );
    std::string text() const;
    void move( const cDataPoint& r );
    void clear();
    void add( dp_t p );
    std::vector< dp_t >& points();
    cDataPoint& center();
private:
    cDataPoint myCenter;
    std::vector< dp_t > myPoints;
};

/** Locate clusters using K-Means algorithm
 https://en.wikipedia.org/wiki/K-means_clustering
*/
class KMeans
{
public:
    /// Add a data location
    void Add( const std::vector<double>& p );
    void Add( cDataPoint& p );

    /** initialize
        @param[in] clusterCount number of clusters expected
        @parsm[in] frandom true if random initial cluster locations, default false
    */
    void Init(
        int clusterCount,
        bool frandom = false );

    /// Assign locations to nearest cluster
    void Assign();

    /// Move cluster to mean of assigned locations
    void MoveClustersToMean();

    /// Run KMeans iteration maximum number of times ( 10 is reasonable )
    void Iter( int max );

    /// Total distance beween all locations and their assigned cluster
    double TotalDistanceToCluster();

    /// Text showing location assignemnts to clusters
    std::string text();

    std::string ClusterStats( int cluster );

    std::vector< cCluster >&
    clusters();



private:
    std::vector< dp_t > myLocations;       // locations of data
    int myClusterCount;
    std::vector< cCluster > myClusters;         // clusters
    std::vector< int > myAssigns;        // cluster indices locations assigned to

    void ClusterLocationInitIndex();
    void ClusterLocationInitRandom();
};

