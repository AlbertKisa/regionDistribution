#include "RegionDivision.h"

#define N 9999


int main()
{
    int numUSV = 12;
    vector<vector<int>>abilityUSV = {{200, 150, 200, 150, 200, 150, 200, 150, 200, 150, 200, 150},
                                     {120, 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 90,}};
    vector<int>numSwarm = {3, 3, 3, 2};
    srand(time(NULL));
    // vector<vector<int>>groupCenterPoint = {{-1000 + 10000 * rand()%(N + 1)/(float)(N + 1), -1000 + 10000 * rand()%(N + 1)/(float)(N + 1),  3000 + 10000 * rand()%(N + 1)/(float)(N + 1), 3000 + 10000 * rand()%(N + 1)/(float)(N + 1)},
    //                                        {-1000 + 10000 * rand()%(N + 1)/(float)(N + 1),  1000 + 10000 * rand()%(N + 1)/(float)(N + 1), -1000 + 10000 * rand()%(N + 1)/(float)(N + 1), 1000 + 10000 * rand()%(N + 1)/(float)(N + 1)}};
    vector<vector<int>>groupCenterPoint = {{-1000, -1000,  3000, 3000},
                                           {-1000,  1000, -1000, 1000}};  
    vector<vector<int>>mission_area_coor = {{35000, 5000, 5000, 35000}, {5000, 5000, 25000, 25000}};
    RegionDiv reg(4.0);
    vector<double>dUSwarm;
    double summ;
    vector<double>aa = {1.1, 1.2, 1.3};
    vector<double>dd;
    dd = reg.calswarm_ability(abilityUSV, numSwarm);
    cout<<dd[0]<<" "<<dd[1]<<" "<<dd[2]<<" "<<dd[3]<<" "<<endl;
    summ = reg.vector_sum(aa);
    cout<<"123"<<endl;
 
    
    return 0;
    
}
