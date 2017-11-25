/***********
�����㷨   ���ڱ�ǩ
***********/

#ifndef LPACLUSTER_H 
#define LPACLUSTER_H

#include "baseInformation.h"


class LpaCluster
{
public:
	LpaCluster();
	~LpaCluster();

	vector<vector<unsigned int> > getCluster(unsigned int node_sum, 
		                                     vector<pair<unsigned int, unsigned int> >& t_relation, 
		                                     int iter_times,
		                                     int type = 1);//��ȡ���ŷָ�, iter_times ��������, 
	                                                       //type = 1 ÿ���ڵ�ֻ����һ����ǩ

private:
	void initial(unsigned int node_sum, vector<pair<unsigned int, unsigned int> >& t_relation);//��ʼ���ڵ㼰��ر�ǩ

	void doRun(int iter_times);

	//ɾ���м���̲���Ҫ�ı���
	void deleteTempVar();

private:
	int m_type;//��ǩѡ��ģʽ

	vector<pair<unsigned int, unsigned int> > m_relation_vec;

	Node* m_node_vec;

	unsigned int m_node_sum;
};


#endif