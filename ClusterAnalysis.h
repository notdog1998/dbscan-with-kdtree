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

//�����������
class ClusterAnalysis
{
private:
	vector<DataPoint> dadaSets;        //���ݼ���
	unsigned int dimNum;            //ά��
	double radius;                    //�뾶
	unsigned int dataNum;            //��������
	unsigned int minPTs;            //������С���ݸ���

	double GetDistance(DataPoint& dp1, DataPoint& dp2);                    //���뺯��
	void SetArrivalPoints(DataPoint& dp);                                //�������ݵ��������б�
	void KeyPointCluster(unsigned long i, unsigned long clusterId);    //�����ݵ������ڵĵ�ִ�о������
public:

	ClusterAnalysis(){}                    //Ĭ�Ϲ��캯��
	bool Init(char* fileName, double radius, int minPTs);    //��ʼ������
	bool DoDBSCANRecursive();            //DBSCAN�ݹ��㷨
	bool WriteToFile(char* fileName);    //��������д���ļ�

	
	//kd������
//	sx = x - radius, tx = x + radius,sy = y - radius, ty = y + radius;
// 	bool cmpX(const DataPoint &a,const DataPoint &b);
// 	bool cmpY(const DataPoint &a,const DataPoint &b);
//	vector<DataPoint> dadaSets_save;
	int make_kdtree(int left, int right, int depth);
	void RangeSearch(DataPoint &dp, int u, const double & sx, const double & tx, const double & sy, const double & ty, int depth);
};