#include <vector>

#include "cRow.h"

class cCluster
{
public:
    cCluster( const cRow& r );
    double dist( const cRow& o );
    std::string text() const;
    void move( const cRow& r );
private:
    cRow myCenter;
};

/** Locate clusters using K-Means algorithm
 https://en.wikipedia.org/wiki/K-means_clustering
*/
class KMeans
{
public:
    /// Add a data location
    void Add( const cRow& p );

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

private:
    std::vector< cRow > myLocations;       // locations of data
    int myClusterCount;
    std::vector< cCluster > myClusters;         // clusters
    std::vector< int > myAssigns;        // cluster indices locations assigned to

    void ClusterLocationInitIndex();
    void ClusterLocationInitRandom();
};

