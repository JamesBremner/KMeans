#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

#include "cDataPoint.h"
#include "KMeans.h"

int main( int argc, char* argv[] )
{
    try {
    if( argc != 4 ) {
        std::cout << "Usage: KMeans <data dimension> <data file path> <number of clusters>\n";
        exit(1);
    }
    int datadim = atoi( argv[1] );
    KMeans KM;
    vector< cDataPoint > Clusters;
    ifstream f( argv[2]);
    if( ! f.is_open() ) {
        cout << "cannot open " <<  argv[2] << "\n";
        return 1;
    }
    cDataPoint l(datadim);
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
        for( int k = 0; k < datadim; k++ )
            l.d[k] = atof(output[k].c_str());
        //cout << "saving " << l.Text() << "\n";
        KM.Add( l );
    }

    KM.Init( atoi( argv[3] ), false );

    for( int kiter=0; kiter < 10; kiter++ )
    {
        KM.Assign();
        //cout << KM.AssignText();
        KM.MoveClustersToMean();
        std::cout << "Total distance " << KM.TotalDistanceToCluster() << "\n";
    }

    cout << KM.text();

    }
    catch( std::runtime_error& e )
    {
        cout << e.what() << "\n";
    }

    return 0;
}
