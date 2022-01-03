#include "Circle.h"

int main()
{
    double aaa;
    aaa = pow(0.5,2);

    Circle c(3);
    vector<vector<double>>a = {{1.1, 1.2, 1.3},{1.2, 1.4}};
    vector<vector<double>>* b = &a;
    cout<<a[0].size()<<endl;
    cout<<(*b)[0].size()<<endl;

    cout<<"Area="<<c.Area()<<endl;
    string ss;
    cout<<"输入你的名字:"<<endl;
    cin>>ss;
    cout<<"谢谢输入，测试结束！"<<endl;
    return 1;
}   