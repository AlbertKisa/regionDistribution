#ifndef _REGION_DIVISION_
#define _REGION_DIVISION_

#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<numeric>
#include<algorithm>
#include<math.h>

using namespace std;

#define PI 3.14159
// int g_N = 999;              //控制随机数0~1的精度，9表示精度为小数点后1位，99表示精度为小数点后2位，999表示精度为小数点后3位，9999表示精度为小数点后4位  


class RegionDiv
{
private:
    double m_r;                 //测试参数
public:
    RegionDiv();
    RegionDiv(double r);
    //USV编组探测范围计算函数
    vector<double> calswarm_ability(vector<vector<int>> &abilityUSV, vector<int> &numswarm);
    //vector求和函数
    double vector_sum(const vector<double> &detad);
};

#endif