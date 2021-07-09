#include "DataPoint.h"

//Ĭ�Ϲ��캯��
DataPoint::DataPoint()
{
}

//���캯��
DataPoint::DataPoint(unsigned long dpID, double* dimension, bool isKey) :isKey(isKey), dpID(dpID)
{
	//����ÿά��ά������
	for (int i = 0; i<DIME_NUM; i++)
	{
		this->dimension[i] = dimension[i];
	}
}

//����ά������
void DataPoint::SetDimension(double* dimension)
{
	for (int i = 0; i<DIME_NUM; i++)
	{
		this->dimension[i] = dimension[i];
	}
}

//��ȡά������
double* DataPoint::GetDimension()
{
	return this->dimension;
}

//��ȡ�Ƿ�Ϊ���Ķ���
bool DataPoint::IsKey()
{
	return this->isKey;
}

//���ú��Ķ����־
void DataPoint::SetKey(bool isKey)
{
	this->isKey = isKey;
}

//��ȡDpId����
unsigned long DataPoint::GetDpId()
{
	return this->dpID;
}

//����DpId����
void DataPoint::SetDpId(unsigned long dpID)
{
	this->dpID = dpID;
}

//GetIsVisited����
bool DataPoint::isVisited()
{
	return this->visited;
}


//SetIsVisited����
void DataPoint::SetVisited(bool visited)
{
	this->visited = visited;
}

//GetClusterId����
long DataPoint::GetClusterId()
{
	return this->clusterId;
}

//GetClusterId����
void DataPoint::SetClusterId(long clusterId)
{
	this->clusterId = clusterId;
}

//GetArrivalPoints����
vector<unsigned long>& DataPoint::GetArrivalPoints()
{
	return arrivalPoints;
}