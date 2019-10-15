#include <iostream>

#include "KMeans.h"
#include "CrossCorrelation.h"
#include "LinearRegression.h"

using namespace std;

void KMeansTest()
{
    KMeans KM;

    KM.Add( cRow( {0,0,0,0} ));
    KM.Add( cRow( {0,0,0,10} ));
    KM.Add( cRow( {0,0,0,9} ));

    KM.Init( 2 );

    KM.Assign();

    cout <<"\n"<< KM.AssignText() << "\n";

    KM.MoveClustersToMean();

    cout <<"\n"<< KM.AssignText() << "\n";
}

void CorrelationTest()
{
    std::vector<double> X {43, 21, 25, 42, 57, 59};
    std::vector<double> Y {99, 65, 79, 75, 87, 81};
    double c = correlationCoefficient( X, Y );
    if( fabs( c - 0.5298 ) > 0.0001 )
        cout << "failed " << c << "\n";
    std::vector<double> X2 {15, 18, 21, 24, 27};
    std::vector<double> Y2 {25, 25, 27, 31, 32};
    c = correlationCoefficient( X2, Y2 );
    if( fabs( c - 0.9534 ) > 0.0001 )
        cout << "failed 2 " << c << "\n";
}

void LinearRegressionTest()
{
    std::vector<double> X {15, 18, 21, 24, 27};
    std::vector<double> Y {25, 25, 27, 31, 32};

    auto r = regression( X, Y );
    //cout << r.first <<" "<< r.second << "\n";
    for( int k = 0; k < (int)X.size(); k++ )
    {
        int ycalc = r.first + r.second * X[k];
        if( fabs( ycalc - Y[k] > 1 ) )
           cout << "failed LinearRegressionTest\n";
    }
}

int main()
{
    //KMeansTest();

    CorrelationTest();

    LinearRegressionTest();

    return 0;
}
