#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

#include "cP.h"
#include "KMeans.h"

int main( int arc, char* argv[] )
{
    KMeans KM;
    vector< cP > Clusters;
    ifstream f( argv[1]);
    if( ! f.is_open() )
        cout << "cannot open " <<  argv[1] << "\n";
    cP l;
    string line;
    while( getline( f, line ) )
    {
        std::stringstream sst(line);
        std::string a;
        vector<string> output;
        while( getline( sst, a, ',' ) )
            output.push_back(a);
        if( ! output.size() )
            continue;
        l.x = atof(output[0].c_str());
        l.y = atof(output[1].c_str());
        l.z = atof(output[2].c_str());
        //cout << "saving " << l.Text() << "\n";
        KM.Add( l );
    }

    KM.ClusterCount( 3 );

    for( int kiter=0; kiter < 10; kiter++ )
    {
        KM.Assign();
        //cout << KM.AssignText();
        KM.MoveClustersToMean();
        std::cout << "Total distance " << KM.TotalDistanceToCluster() << "\n";
    }

    return 0;
}
