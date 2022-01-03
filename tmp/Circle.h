#ifndef CIRCLE_H
#define CIRCLE_H
#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

class Circle
{
private:
    double r;//半径
public:
    Circle();//构造函数
    Circle(double R);//构造函数
    double Area();//求面积函数
};

#endif