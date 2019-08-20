#include <vector>

#include "cRow.h"

/** Locate clusters using K-Means algorithm
 https://en.wikipedia.org/wiki/K-means_clustering
*/
class KMeans
{
public:
    /// Add a data location
    void Add( const cRow& p )
    {
        myLocations.push_back( p );
    }

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
    std::string AssignText();

    std::string ClusterStats( int cluster );

private:
    std::vector< cRow > myLocations;       // locations of data
    int myClusterCount;
    std::vector< cRow > myClusters;         // cluster centers
    std::vector< int > myAssigns;        // cluster indices locations assigned to

    void ClusterLocationInitIndex();
    void ClusterLocationInitRandom();
};

