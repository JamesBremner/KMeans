#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <wex.h>
#include "cStarterGUI.h"
#include "cDataPoint.h"
#include "KMeans.h"

class cLoc
{
public:
    double x;
    double y;
};

class cSolution
{
public:

    void generate();
    void findClusters();

    void draw(wex::shapes &S);

private:
    std::vector<cLoc> myData;
    std::vector<cLoc> myClusterCenter;

    cLoc panZoom(const cLoc &loc);
};

void cSolution::generate()
{
    // scatter datapoints at random throughout a 100 by 100 area
    srand(time(NULL));
    for (int k = 0; k < 30; k++)
    {
        cLoc loc;
        loc.x = rand() % 100;
        loc.y = rand() % 100;
        myData.push_back(loc);
    }

    // scatter datapoints at random in four clusters of 10 by 10 area
    for (int kc = 0; kc < 4; kc++)
    {
        for (int kp = 0; kp < 40; kp++)
        {
            cLoc loc;
            loc.x = rand() % 10 + 20 * kc;
            loc.y = rand() % 10 + 20 * kc;
            myData.push_back(loc);
        }
    }
}

void cSolution::findClusters()
{
    // Construct the KMeans class
    KMeans KM;

    // loop over data
    for (auto &l : myData)
    {
        // construct data point
        cDataPoint dp(2);
        dp.d[0] = l.x;
        dp.d[1] = l.y;

        // add data point to KMeans
        KM.Add(dp);
    }

    // Initialize KMeans with required number of clusters
    KM.Init(4, false);

    // run KMeans algorithm to find clusters
    KM.Iter( 10 );

    // store cluster centers
    for (auto &c : KM.clusters())
    {
        cLoc l;
        l.x = c.center().d[0];
        l.y = c.center().d[1];
        myClusterCenter.push_back(l);
    }
}

cLoc cSolution::panZoom(const cLoc &loc)
{
    const int scale = 5;
    const int panx = 20;
    const int pany = 20;

    cLoc ret;
    ret.x = panx + scale * loc.x;
    ret.y = pany + scale * loc.y;
    return ret;
}

void cSolution::draw(wex::shapes &S)
{
    int scale = 10;

    S.color(0x0000FF);
    S.fill( false );
    for( auto& l : myClusterCenter )
    {
        auto sl = panZoom( l );
        S.circle(
            sl.x, sl.y,
            20);
    }
    
    S.color(0xFF0000);
    S.fill( true );
    for( auto& l : myData )
    {
        auto sl = panZoom( l );
        S.circle(
            sl.x, sl.y,
            2);
    }


}

class cGUI : public cStarterGUI
{
public:
    cGUI()
        : cStarterGUI(
              "xyClusters",
              {50, 50, 1000, 500})
    {

        mySolution.generate();
        mySolution.findClusters();

        show();
        run();
    }

    void draw( wex::shapes& S )
    {
        mySolution.draw( S );
    }

private:
    cSolution mySolution;
};

main()
{
    cGUI theGUI;
    return 0;
}
