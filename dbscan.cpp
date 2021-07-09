#include "ClusterAnalysis.h"
#include <cstdio>
#include <ctime>

using namespace std;

int main()
{
	clock_t start, finish;
	start = clock();
	ClusterAnalysis myClusterAnalysis;                        //�����㷨��������
	myClusterAnalysis.Init("test_data01.txt", 10, 5);        //�㷨��ʼ��������ָ���뾶Ϊ15����������С���ݵ����Ϊ3�����ڳ�������ָ������ά��Ϊ2��
	myClusterAnalysis.DoDBSCANRecursive();                    //ִ�о����㷨
	myClusterAnalysis.WriteToFile("result.txt");//дִ�к�Ľ��д���ļ�
	finish = clock();
	cout << endl << finish - start << "/" << CLOCKS_PER_SEC << "(s)" << endl;
	system("pause");    //��ʾ���
	return 0;            //����
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        