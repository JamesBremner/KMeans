#include <iostream>

#include "KMeans.h"

using namespace std;


int main()
{
    KMeans KM;

    KM.Add( cRow( {0,0,0,0} ));
    KM.Add( cRow( {0,0,0,10} ));
    KM.Add( cRow( {0,0,0,9} ));

    KM.ClusterCount( 2 );

    KM.Assign();

    cout <<"\n"<< KM.AssignText() << "\n";

    KM.MoveClustersToMean();

    cout <<"\n"<< KM.AssignText() << "\n";

    return 0;
}
