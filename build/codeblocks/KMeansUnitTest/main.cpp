#include <iostream>
#include "cutest.h"
#include "cDataPoint.h"
#include "KMeans.h"

using namespace std;

TEST( dist )
{
    cDataPoint a( { 10, 10 });
    cDataPoint b( { 20, 20 });
    CHECK_CLOSE( 14.1, cDataPoint::dist( a, b), 0.1 );
}

TEST( KMeans )
{
    KMeans K;
    K.Add( { 10, 10 } );
    K.Add( { 11,  9 }  );
    K.Add( { 20, 10 } );
    K.Add( { 21, 12 } );
    K.Init(2);
    K.Iter( 3 );
    CHECK_EQUAL( 2, K.clusters()[0].points().size() );
    CHECK_EQUAL( 2, K.clusters()[1].points().size() );
    CHECK_CLOSE( 10.5, K.clusters()[0].center().d[0], 0.01);
    CHECK_CLOSE( 9.5, K.clusters()[0].center().d[1], 0.01);
    CHECK_CLOSE( 20.5, K.clusters()[1].center().d[0], 0.01);
    CHECK_CLOSE( 11, K.clusters()[1].center().d[1], 0.01);
}

int main()
{
    raven::set::UnitTest::RunAllTests();
    return 0;
}
