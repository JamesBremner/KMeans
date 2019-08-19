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

    /// Set mumber of clusters expected and initialize
    void ClusterCount( int c );

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
};

