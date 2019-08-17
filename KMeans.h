
/** Locate clusters using K-Means algorithm
 https://en.wikipedia.org/wiki/K-means_clustering
*/
class KMeans
{
public:
    /// Add a data location
    void Add( cP& p )
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

private:
    vector< cP > myLocations;       // locations of data
    int myClusterCount;
    vector< cP > myClusters;         // cluster centers
    vector< int > myAssigns;        // cluster indices locations assigned to
};

