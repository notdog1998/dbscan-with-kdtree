#include "ClusterAnalysis.h" 

//kdtree������ʼ��
struct node
{
	int parent, left, right;
	int location;
};
node nd[MAXN];
int node_counter = 0;
const int NIL = -1;
//kd������
bool cmpX(DataPoint &a,DataPoint &b)
{
//	return a.dimension[0] < b.dimension[0];
	return a.GetDimension()[0] < b.GetDimension()[0];
}
bool cmpY(DataPoint &a,DataPoint &b)
{
	return a.GetDimension()[1] < b.GetDimension()[1];
}

int ClusterAnalysis::make_kdtree(int left, int right, int depth)
{
	if (left >= right)
	{
		return NIL;
	}

	int t = node_counter++;

	if (depth % 2 == 0)
	{
		sort(dadaSets.begin()+left, dadaSets.begin()+right, cmpX);
//		sort(dadaSets + left, dadaSets + right, cmpX);
	}
	else
	{
//		sort(dadaSets + left, dadaSets + right, cmpY);
		sort(dadaSets.begin() + left, dadaSets.begin() + right, cmpY);
	} 

	int mid = (left + right) / 2;

	nd[t].location = mid;
	nd[t].left = make_kdtree(left, mid, depth + 1);
	nd[t].right = make_kdtree(mid + 1, right, depth + 1);
	return t;
}
void ClusterAnalysis::RangeSearch(DataPoint &dp,int u, const double & sx, const double & tx, const double & sy, const double & ty, int depth)
{
	double x = dadaSets[nd[u].location].GetDimension()[0];
	double y = dadaSets[nd[u].location].GetDimension()[1];

	if (x >= sx && x <= tx && y >= sy && y <= ty&& dadaSets[nd[u].location].GetDpId()!=dp.GetDpId())
	{
//		dp.arrivalPoints_kd.push_back(dadaSets[nd[u].location]);
		double distance = GetDistance(dadaSets[nd[u].location], dp);
		if (distance<=radius)
		{
			dp.GetArrivalPoints().push_back(dadaSets[nd[u].location].GetDpId());
		}
		//dp.GetArrivalPoints().push_back(dadaSets[nd[u].location].dpID);
	}
	if (depth % 2 == 0)
	{
		if (nd[u].left != NIL)
		{
			if (sx <= x)
				RangeSearch(dp,nd[u].left, sx, tx, sy, ty, depth + 1);
		}
		if (nd[u].right != NIL)
			if (x <= tx)
				RangeSearch(dp,nd[u].right, sx, tx, sy, ty, depth + 1);
	}
	else
	{
		if (nd[u].left != NIL)
			if (sy <= y)
				RangeSearch(dp,nd[u].left, sx, tx, sy, ty, depth + 1);

		if (nd[u].right != NIL)
			if (y <= ty)
				RangeSearch(dp,nd[u].right, sx, tx, sy, ty, depth + 1);
	}
}




double stringToDouble(string i) {
	stringstream sf;
	double score = 0;
	sf << i;
	sf >> score;
	return score;
}


/*
�����������ʼ������
˵�����������ļ������뾶��������С���ݸ�����Ϣд������㷨�࣬��ȡ�ļ�����������Ϣ����д���㷨�����ݼ�����
������
char* fileName;    //�ļ���
double radius;    //�뾶
int minPTs;        //������С���ݸ���
����ֵ�� true;    */
bool ClusterAnalysis::Init(char* fileName, double radius, int minPTs)
{
	this->radius = radius;        //���ð뾶
	this->minPTs = minPTs;        //����������С���ݸ���
	this->dimNum = DIME_NUM;    //��������ά��
//	ifstream ifs(fileName);        //���ļ�
	ifstream ifs;
	ifs.open(fileName, ios::in);


	if (!ifs.is_open())                //���ļ��Ѿ����򿪣���������Ϣ
	{
		cout << "Error opening file";    //���������Ϣ
		exit(-1);                        //�����˳�
	}

	unsigned long data_count = 0;            //���ݸ���ͳ��
	while (!ifs.eof())                //���ļ��ж�ȡPOI��Ϣ����POI��Ϣд��POI�б���
	{
		DataPoint tempDP;                //��ʱ���ݵ����
		double tempDimData[DIME_NUM];    //��ʱ���ݵ�ά����Ϣ

		string temp;
		ifs >> temp;
		int split = temp.find(',', 0);
		tempDimData[0] = stringToDouble(temp.substr(0, split));
		tempDimData[1] = stringToDouble(temp.substr(split+1, temp.length()-1));

		tempDP.SetDimension(tempDimData);    //��ά����Ϣ�������ݵ������

		tempDP.SetDpId(data_count);                    //�����ݵ����ID����Ϊi
		tempDP.SetVisited(false);            //���ݵ����isVisited����Ϊfalse
		tempDP.SetClusterId(-1);            //����Ĭ�ϴ�IDΪ-1
		dadaSets.push_back(tempDP);            //������ѹ�����ݼ�������
//		dadaSets[data_count] = tempDP;
		data_count++;        //����+1
	}
	ifs.close();        //�ر��ļ���
	dataNum = data_count;            //�������ݶ��󼯺ϴ�СΪi
	cout << "��������: " << dataNum << " ��" << endl;
	int size = dadaSets.size();
//	vector<DataPoint> &dadaSets_save = dadaSets;

	int root = make_kdtree(0, dataNum, 0);
	for (int i = 0; i < dataNum;++i)
	{
		dadaSets[i].SetDpId(i);
	}
	cout << "build ketree successfully!" << endl;

	for (unsigned long i = 0; i<dataNum; i++)
	{
		const double sx = dadaSets[i].GetDimension()[0] - radius, tx = dadaSets[i].GetDimension()[0] + radius,
			sy = dadaSets[i].GetDimension()[1] - radius, ty = dadaSets[i].GetDimension()[1] + radius;
		RangeSearch(dadaSets[i],root,sx,tx,sy,ty,0);
		if(dadaSets[i].GetArrivalPoints().size()>=minPTs)
//		if (dadaSets[i].arrivalPoints.size() >= minPTs)
		{
			dadaSets[i].SetKey(true);
		}
		else
		{
			dadaSets[i].SetKey(false);
		}

		//show for debug
//		linyue_size.push_back(dadaSets[i].arrivalPoints.size());
//  		cout << "���������" << dadaSets_save[i].arrivalPoints.size() << " ����㣺"<<endl;
// 		cout << dadaSets_save[i].dimension[0] << ' ' << dadaSets_save[i].dimension[1] << ":"<<endl;
// 		for (int k = 0; k < dadaSets_save[i].arrivalPoints.size();++k)
// 		{
// 			cout << k << ':';
// 			cout << dadaSets_save[dadaSets[i].arrivalPoints[k]].dimension[0] << ' '
// 				<< dadaSets_save[dadaSets[i].arrivalPoints[k]].dimension[1] << endl;
// 		}
// 		cout << "*******************" << endl;
// 		cout << "������������" <<linyu_count++ << endl;
//		SetArrivalPoints(dadaSets[i]);            //�������ݵ������ڶ���
	}
// 	sort(linyue_size.begin(), linyue_size.end());
// 	for (int j = 0; j < linyue_size.size();++j)
// 	{
// 		cout << j << ':' << linyue_size[j] << endl;
// 	}
	cout << "������������" << endl;
	return true;    //����
}

/*
���������Ѿ��������㷨��������ݼ���д���ļ�
˵�������Ѿ���������д���ļ�
������
char* fileName;    //Ҫд����ļ���
����ֵ�� true    */
bool ClusterAnalysis::WriteToFile(char* fileName)
{
	ofstream of1(fileName);                                //��ʼ���ļ������
	for (unsigned long i = 0; i<dataNum; i++)                //�Դ������ÿ�����ݵ�д���ļ�
	{
		for (int d = 0; d<DIME_NUM; d++)                    //��ά����Ϣд���ļ�
			of1 << dadaSets[i].GetDimension()[d] << '\t';
		of1 << dadaSets[i].GetClusterId() << endl;        //��������IDд���ļ�
	}
	of1.close();    //�ر�����ļ���
	return true;    //����
}


/*
�������������ݵ��������б�
˵�����������ݵ��������б�
������
����ֵ�� true;    */
void ClusterAnalysis::SetArrivalPoints(DataPoint& dp)
{
	for (unsigned long i = 0; i<dataNum; i++)                //��ÿ�����ݵ�ִ��
	{
		double distance = GetDistance(dadaSets[i], dp);    //��ȡ���ض���֮��ľ���
		if (distance <= radius && i != dp.GetDpId())        //������С�ڰ뾶�������ض����id��dp��id��ִͬ��
			dp.GetArrivalPoints().push_back(i);            //���ض���idѹ��dp�������б���
	}
	if (dp.GetArrivalPoints().size() >= minPTs)            //��dp���������ݵ�������> minPTsִ��
	{
		dp.SetKey(true);    //��dp���Ķ����־λ��Ϊtrue
		return;                //����
	}
	dp.SetKey(false);    //���Ǻ��Ķ�����dp���Ķ����־λ��Ϊfalse
}


/*
������ִ�о������
˵����ִ�о������
������
����ֵ�� true;    */
bool ClusterAnalysis::DoDBSCANRecursive()
{
	unsigned long clusterId = 0;                        //����id��������ʼ��Ϊ0
	for (unsigned long i = 0; i<dataNum; i++)            //��ÿһ�����ݵ�ִ��
	{
		DataPoint& dp = dadaSets[i];                    //ȡ����i�����ݵ����
		if (!dp.isVisited() && dp.IsKey())            //������û�����ʹ��������Ǻ��Ķ���ִ��
		{
			dp.SetClusterId(clusterId);                //���øö���������IDΪclusterId
			dp.SetVisited(true);                    //���øö����ѱ����ʹ�
			KeyPointCluster(i, clusterId);            //�Ըö��������ڵ���о���
			clusterId++;                            //clusterId����1
		}
//		cout << "������\T" << i << endl;
	}

	cout << "������" << clusterId << "��" << endl;        //�㷨��ɺ�����������
	return true;    //����
}

/*
�����������ݵ������ڵĵ�ִ�о������
˵�������õݹ�ķ�����������Ⱦ�������
������
unsigned long dpID;            //���ݵ�id
unsigned long clusterId;    //���ݵ�������id
����ֵ�� void;    */
void ClusterAnalysis::KeyPointCluster(unsigned long dpID, unsigned long clusterId)
{
	DataPoint& srcDp = dadaSets[dpID];        //��ȡ���ݵ����
	if (!srcDp.IsKey())    return;
	
	vector<unsigned long>& arrvalPoints = srcDp.GetArrivalPoints();        //��ȡ���������ڵ�ID�б�
//	for(unsigned long i = 0; i<srcDp.arrivalPoints.size(); i++)
	for (unsigned long i = 0; i<arrvalPoints.size(); i++)
	{
//		DataPoint& desDp = dadaSets[srcDp.arrivalPoints_kd[i].dpID];
		DataPoint& desDp = dadaSets[arrvalPoints[i]];    //��ȡ�����ڵ����ݵ�
		if (!desDp.isVisited())                            //���ö���û�б����ʹ�ִ��
		{
			//cout << "���ݵ�\t"<< desDp.GetDpId()<<"����IDΪ\t" <<clusterId << endl;
			desDp.SetClusterId(clusterId);        //���øö��������ص�IDΪclusterId�������ö����������
			desDp.SetVisited(true);                //���øö����ѱ�����
			if (desDp.IsKey())                    //���ö����Ǻ��Ķ���
			{
				KeyPointCluster(desDp.GetDpId(), clusterId);    //�ݹ�ضԸ���������ݵ������ڵĵ�ִ�о������������������ȷ���
			}
		}
	}
}

//�����ݵ�֮�����
/*
��������ȡ�����ݵ�֮�����
˵������ȡ�����ݵ�֮���ŷʽ����
������
DataPoint& dp1;        //���ݵ�1
DataPoint& dp2;        //���ݵ�2
����ֵ�� double;    //����֮��ľ���        */
double ClusterAnalysis::GetDistance(DataPoint& dp1, DataPoint& dp2)
{
	double distance = 0;        //��ʼ������Ϊ0
	for (int i = 0; i<DIME_NUM; i++)    //������ÿһά����ִ��
	{
		distance += pow(dp1.GetDimension()[i] - dp2.GetDimension()[i], 2);    //����+ÿһά���ƽ��
	}
	return pow(distance, 0.5);        //���������ؾ���
}