/***********
聚类算法   基于标签
***********/

#ifndef LPACLUSTER_H 
#define LPACLUSTER_H

#include "baseInformation.h"


class LpaCluster
{
public:
	LpaCluster(unsigned int node_sum, vector<pair<unsigned int, unsigned int> >& t_relation);

	vector<vector<unsigned int> > getCluster(int iter_times);//获取社团分割, iter_times 迭代次数

private:
	void initial(unsigned int node_sum, vector<pair<unsigned int, unsigned int> >& t_relation);//初始化节点及相关标签

	void doRun(int iter_times, int type = 1);//type = 1 每个节点只保留一个标签
private:
	vector<pair<unsigned int, unsigned int> > m_relation_vec;

	Node* m_node_vec;

	unsigned int m_node_sum;
};


#endif