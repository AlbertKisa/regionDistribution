#include "RegionDivision.h"

#define N 9999


int main()
{
    //数据加载
    // int numUSV = 12;                //USV总数量
    vector<vector<int>>abilityUSV = {{200, 150, 200, 150, 200, 150, 200, 150, 200, 150, 200, 150},              //USV的探测距离和角度
                                     {120, 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 90,}};
    vector<int>numSwarm = {3, 3, 3, 2};             //编组数量
    // srand(time(NULL));
    // vector<vector<int>>groupCenterPoint = {{-1000 + 10000 * rand()%(N + 1)/(float)(N + 1), -1000 + 10000 * rand()%(N + 1)/(float)(N + 1),  3000 + 10000 * rand()%(N + 1)/(float)(N + 1), 3000 + 10000 * rand()%(N + 1)/(float)(N + 1)},
    //                                        {-1000 + 10000 * rand()%(N + 1)/(float)(N + 1),  1000 + 10000 * rand()%(N + 1)/(float)(N + 1), -1000 + 10000 * rand()%(N + 1)/(float)(N + 1), 1000 + 10000 * rand()%(N + 1)/(float)(N + 1)}};
    vector<vector<int>>groupCenterPoint = {{-1000, -1000,  3000, 3000},             //编组的中心位置
                                           {-1000,  1000, -1000, 1000}};  
    vector<vector<int>>mission_area_coor = {{35000, 5000, 5000, 35000},             //任务区域的顶点坐标
                                            {5000, 5000, 25000, 25000}};           

    //区域划分与分配计算
    RegionDiv reg(4.0);

    vector<double>dUSwarm;          //存储USV编组的探测距离   
    dUSwarm = reg.calswarm_ability(abilityUSV, numSwarm);       //计算USV编组的探测距离
    cout<<dUSwarm[0]<<" "<<dUSwarm[1]<<" "<<dUSwarm[2]<<" "<<dUSwarm[3]<<" "<<endl;

    vector<double> tmp;
    int direction = 1;
    tmp = reg.areaassignment(mission_area_coor, groupCenterPoint, dUSwarm, direction);
    
    return 0;
    
}
