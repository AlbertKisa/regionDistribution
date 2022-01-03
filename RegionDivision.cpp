#include"RegionDivision.h"

RegionDiv::RegionDiv()
{
    this->m_r = 5.0;
}

RegionDiv::RegionDiv(double r)
{
    this->m_r = r;
}

vector<double> RegionDiv::calswarm_ability(const vector<vector<int>> &abilityUSV, const vector<int> &numswarm)
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

vector<double> RegionDiv::areaassignment(const vector<vector<int>> &mission_area_coor, const vector<vector<int>> &groupCenterPoint, vector<double> &duswarm, int direction)
{
    int numgroup = duswarm.size();
    
    
    //定义区域的四个顶点，并将输入区域四个角的坐标转换为数组
    int p1[2][1] = {{mission_area_coor[0][0]},{mission_area_coor[1][0]}};
    int p2[2][1] = {{mission_area_coor[0][1]},{mission_area_coor[1][1]}};
    int p3[2][1] = {{mission_area_coor[0][2]},{mission_area_coor[1][2]}};
    int p4[2][1] = {{mission_area_coor[0][3]},{mission_area_coor[1][3]}};

    //计算矩形的长和宽
    double mission_len;             //长
    double mission_wid;             //宽

    mission_len = cal_distance(p1, p2);
    mission_wid = cal_distance(p2, p3);

    if((mission_len < mission_wid && direction == 0) || (mission_len > mission_wid && direction == 1)){

        p1[0][0] = mission_area_coor[0][1];
        p1[1][0] = mission_area_coor[1][1];

        p2[0][0] = mission_area_coor[0][2];
        p2[1][0] = mission_area_coor[1][2];

        p3[0][0] = mission_area_coor[0][3];
        p3[1][0] = mission_area_coor[1][3];

        p4[0][0] = mission_area_coor[0][0];
        p4[1][0] = mission_area_coor[1][0];

    }

    int area_assign_index[numgroup] = {0};     //区域分配向量

    //判断是否为空  
    if(!groupCenterPoint.empty()){
        //计算旋转角
        double thetarad = -atan2(p2[1][0] - p1[1][0], p2[0][0] - p1[0][0]);
        //旋转矩阵
        double transmat[2][2] = {{cos(thetarad), -sin(thetarad)},
                                 {sin(thetarad), cos(thetarad)}};
        
        //存储旋转后的任务区域顶点
        int row_transmat = sizeof(transmat)/sizeof(transmat[0]);
        int cow_transmat = sizeof(transmat[0])/sizeof(transmat[0][0]);
        int row_grouppoint = groupCenterPoint.size();
        int cow_grouppoint = groupCenterPoint[0].size();
        float pointtrans[row_transmat][cow_grouppoint];
        
        cout<<"矩阵转换结果"<<endl;
        for(int i =  0; i < row_transmat; i++){
            for(int j = 0; j < cow_grouppoint; j++){
                double matrix_sum = 0;
                for(int k = 0; k < cow_transmat; k++){
                    matrix_sum += transmat[i][k]*groupCenterPoint[k][j];
                }
                pointtrans[i][j] = matrix_sum;
                cout<<pointtrans[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;

        float pointtrans_firstrow[cow_grouppoint];
        for(int i = 0; i < cow_grouppoint; i++){
            pointtrans_firstrow[i] = pointtrans[0][i];
        }
        bubblesort(pointtrans_firstrow, cow_grouppoint, area_assign_index);   
    }
    else{

        for(int i = 0; i < numgroup; i++){
            area_assign_index[i] = i;
        }
    }

    float detectratio[numgroup] = {0};      //探测能力占比
    float dusv_sum = accumulate(duswarm.begin(), duswarm.end(), 0);   //探测能力
    for(int i = 0; i < numgroup; i++){
        detectratio[i] = duswarm[i]/dusv_sum;
    }

    //进行区域分割，并按照次序分配给每组无人艇
    float subareapoint[2][4][numgroup];
    // float subareapoint[2][4][numgroup] = {0};
    int sp1[2][1] = {0};
    int sp2[2][1] = {0};
    int sp3[2][1] = {0};
    int sp4[2][1] = {0};
    int last_p2[2][1] = {0};
    int last_p3[2][1] = {0};
    int j = 0;
    for(int i = 0; i < numgroup; i++){
        j = area_assign_index[i];
        if(i == 0){
            sp1[0][0] = p1[0][0];
            sp1[1][0] = p1[1][0];
            sp2[0][0] = p1[0][0] + detectratio[j] * (p2[0][0] - p1[0][0]);
            sp2[1][0] = p1[1][0] + detectratio[j] * (p2[1][0] - p1[1][0]);
            sp3[0][0] = p4[0][0] + detectratio[j] * (p3[0][0] - p4[0][0]);
            sp3[1][0] = p4[1][0] + detectratio[j] * (p3[1][0] - p4[1][0]);
            sp4[0][0] = p4[0][0];
            sp4[1][0] = p4[1][0];

            subareapoint[0][0][j] = sp1[0][0];
            subareapoint[1][0][j] = sp1[1][0];
            subareapoint[0][1][j] = sp2[0][0];
            subareapoint[1][1][j] = sp2[1][0];
            subareapoint[0][2][j] = sp3[0][0];
            subareapoint[1][2][j] = sp3[1][0];
            subareapoint[0][3][j] = sp4[0][0];
            subareapoint[1][3][j] = sp4[1][0];

            last_p2[0][0] = sp2[0][0];
            last_p2[1][0] = sp2[1][0];

            last_p3[0][0] = sp3[0][0];
            last_p3[1][0] = sp3[1][0];

        }
        else{
            sp1[0][0] = last_p2[0][0];
            sp1[1][0] = last_p2[1][0];
            sp2[0][0] = last_p2[0][0] + detectratio[j] * (p2[0][0] - p1[0][0]);
            sp2[1][0] = last_p2[1][0] + detectratio[j] * (p2[1][0] - p1[1][0]);
            sp3[0][0] = last_p3[0][0] + detectratio[j] * (p3[0][0] - p4[0][0]);
            sp3[1][0] = last_p3[1][0] + detectratio[j] * (p3[1][0] - p4[1][0]);
            sp4[0][0] = last_p3[0][0];
            sp4[1][0] = last_p3[1][0];

            subareapoint[0][0][j] = sp1[0][0];
            subareapoint[1][0][j] = sp1[1][0];
            subareapoint[0][1][j] = sp2[0][0];
            subareapoint[1][1][j] = sp2[1][0];
            subareapoint[0][2][j] = sp3[0][0];
            subareapoint[1][2][j] = sp3[1][0];
            subareapoint[0][3][j] = sp4[0][0];
            subareapoint[1][3][j] = sp4[1][0];

            last_p2[0][0] = sp2[0][0];
            last_p2[1][0] = sp2[1][0];

            last_p3[0][0] = sp3[0][0];
            last_p3[1][0] = sp3[1][0];
        }
    }

    //显示区域分配结果
    cout<<"区域分配结果"<<endl;
    for(int k = 0; k < numgroup; k++){
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 4; j++){
                cout<<subareapoint[i][j][k]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<endl;
    }

    vector<double>mission_ass = {0};

    return mission_ass;

}

double RegionDiv::cal_distance(const int p1[2][1], const int p2[2][1])
{
    double distance;
    int x;
    int y;
    x = abs(p1[0][0] - p2[0][0]);
    y = abs(p1[1][0] - p2[1][0]);
    distance = sqrt(pow(x, 2) + pow(y, 2));
    return distance; 
}

void RegionDiv::bubblesort(const float *p, int length, int * ind_diff)
{
    float pp[length];
    copy(p, p+length, pp);              //将数组P复制给数组pp
	for (int m = 0; m < length; m++)
	{
		ind_diff[m] = m;
	}
 
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length - i - 1; j++)
		{
			if (pp[j] > pp[j + 1])
			{
				float temp = p[j];
				pp[j] = pp[j + 1];
				pp[j + 1] = temp;
 
				int ind_temp = ind_diff[j];
				ind_diff[j] = ind_diff[j + 1];
				ind_diff[j + 1] = ind_temp;
			}
		}
	}

    return;
}
