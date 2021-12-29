#include"RegionDivision.h"

RegionDiv::RegionDiv()
{
    this->m_r = 5.0;
}

RegionDiv::RegionDiv(double r)
{
    this->m_r = r;
}

vector<double> RegionDiv::calswarm_ability(vector<vector<int>> &abilityUSV, vector<int> &numswarm)
{
    int row = numswarm.size();     //USV分组的组数
    int cow = *max_element(numswarm.begin(), numswarm.end());       //编队内的成员数量最大值

    vector<vector<double>>detad(row, vector<double>(cow, 0));       //存储编组内相邻两个USV的探测范围，设置重叠率为0.8

    vector<double>duswarm(row, 0);      //USV编组后，存储每个编组的探测能力
    
    int k_begin = 0;
    int k_end = 0;
    int k = 0;
    for(int i = 0; i < row; i++){
        //计算每组无人艇的探测能力
        double du;
        k = k_begin;
        for(int j = 0; j < numswarm[i] - 1; j++){
            detad[i][j] = (abilityUSV[0][k]*sin(abilityUSV[1][k]*PI/2/180.0) + abilityUSV[0][k + 1]*sin(abilityUSV[1][k + 1]*PI/2/180.0))*0.8;
            k++;
        }
        k_end = k_begin + numswarm[i] - 1;
        double tmp_sum = 0.0;
        tmp_sum = vector_sum(detad[i]);
        du = vector_sum(detad[i]) + abilityUSV[0][k_begin]*sin(abilityUSV[1][k_begin]*PI/2.0/180.0) + abilityUSV[0][k_end]*sin(abilityUSV[1][k_end]*PI/2.0/180.0);
        duswarm[i] = du;
        k_begin = k_begin + numswarm[i];
    }
    return duswarm;

}

double RegionDiv::vector_sum(const vector<double> &detad)
{
    double vectorsum = 0.0;
    for(auto iter = detad.begin(); iter != detad.end(); iter++){
        vectorsum += *iter;
    }
    return vectorsum;
}
