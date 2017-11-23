/***********
�����㷨   ���ڱ�ǩ
***********/

#ifndef LPACLUSTER_H 
#define LPACLUSTER_H

#include "baseInformation.h"


class LpaCluster
{
public:
	LpaCluster(unsigned int node_sum, vector<pair<unsigned int, unsigned int> >& t_relation);

	vector<vector<unsigned int> > getCluster(int iter_times);//��ȡ���ŷָ�, iter_times ��������

private:
	void initial(unsigned int node_sum, vector<pair<unsigned int, unsigned int> >& t_relation);//��ʼ���ڵ㼰��ر�ǩ

	void doRun(int iter_times, int type = 1);//type = 1 ÿ���ڵ�ֻ����һ����ǩ
private:
	vector<pair<unsigned int, unsigned int> > m_relation_vec;

	Node* m_node_vec;

	unsigned int m_node_sum;
};


#endif