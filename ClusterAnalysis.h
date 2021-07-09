#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "DataPoint.h"
#include <cstdio>
#include <algorithm>
#include <fstream>
#include <iosfwd>
#include <math.h>
#include <string>
#include <sstream> 
using namespace std;

#define MAXN 500005

//聚类分析类型
class ClusterAnalysis
{
private:
	vector<DataPoint> dadaSets;        //数据集合
	unsigned int dimNum;            //维度
	double radius;                    //半径
	unsigned int dataNum;            //数据数量
	unsigned int minPTs;            //邻域最小数据个数

	double GetDistance(DataPoint& dp1, DataPoint& dp2);                    //距离函数
	void SetArrivalPoints(DataPoint& dp);                                //设置数据点的领域点列表
	void KeyPointCluster(unsigned long i, unsigned long clusterId);    //对数据点领域内的点执行聚类操作
public:

	ClusterAnalysis(){}                    //默认构造函数
	bool Init(char* fileName, double radius, int minPTs);    //初始化操作
	bool DoDBSCANRecursive();            //DBSCAN递归算法
	bool WriteToFile(char* fileName);    //将聚类结果写入文件

	
	//kd树操作
//	sx = x - radius, tx = x + radius,sy = y - radius, ty = y + radius;
// 	bool cmpX(const DataPoint &a,const DataPoint &b);
// 	bool cmpY(const DataPoint &a,const DataPoint &b);
//	vector<DataPoint> dadaSets_save;
	int make_kdtree(int left, int right, int depth);
	void RangeSearch(DataPoint &dp, int u, const double & sx, const double & tx, const double & sy, const double & ty, int depth);
};