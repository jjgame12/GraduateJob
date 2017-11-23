#include "lpaCluster.h"

#include <iostream>
#include <vector>
#include <map>


LpaCluster::LpaCluster(unsigned int node_sum, vector<pair<unsigned int, unsigned int> >& t_relation)
{	
	initial(node_sum, t_relation);
}

vector<vector<unsigned int> > LpaCluster::getCluster(int iter_times)
{
	initial();//标签初始化，有待优化，目前只用一个标签，且初始化时所有标签不同，可针对性优化

	//开始迭代
	doRun(iter_times);

	//遍历节点容器，将标签一致的节点归为统一一类的社团，并返回社团

}

void LpaCluster::doRun(int iter_times, int type)
{
	//中间变量，作为随机访问节点顺序的参照
	vector<unsigned int> random_order;
	random_order.resize(m_node_sum+1);
	for(unsigned int i = 1;i <= m_node_sum;i++)
	{
		random_order[i] = i;//按照该容器中的元素作为节点的id来达到后续随机访问节点的目的
	}
	
	if(type == 1)//只选择一个标签保留***
	{
		//临时变量
		unsigned int t_id = 1;//当前访问的节点id
		int t_label_size = 1;
		unsigned int* t_label_content = NULL;

		//开始迭代,需要初始化迭代次数吗？以什么作为结束？
		for(int t_iter = 0;t_iter < iter_times;t_iter++)
		{
			//随机打乱节点顺序
			random_shuffle(random_order.begin(), random_order.end());//随机对节点id排序,按照此
			//顺序访问节点

			//对每一个节点，检查周围节点的标签，采用异步的方式更新标签，快速收敛
			for(unsigned int i = 1;i <= m_node_sum;i++)
			{
				t_id = random_order[i];
				vector<unsigned int>& t_neighbor = m_node_vec[t_id].neighbor;

				//对当前节点找到临近节点的标签值数量最大的那个标签
				map<unsigned int, unsigned int> t_label_map;
				for(size_t neighbor_number = 0;neighbor_number < t_neighbor.size();neighbor_number++)
				{
					t_label_map[t_neighbor[neighbor_number]]++;
				}
				

			}

			//若有相同的数目的标签，如何取舍? 保留多个标签？

		}
	}
	

}

void LpaCluster::initial(unsigned int node_sum, vector<pair<unsigned int, unsigned int> >& t_relation)
{
	m_relation_vec = t_relation;

	m_node_sum = node_sum;
	//初始化节点结构
	m_node_vec = new Node[node_sum+1];//m_node_vec的标号代表每一个节点的id，m_node_vec[0]不代表任何节点
    
	//初始化节点标签
	for(unsigned int i = 1;i <= node_sum;i++)
	{
		m_node_vec[i].label_size = 1;//暂时设定标签数目为1***
		m_node_vec[i].label_content = new unsigned int(i);//给初始化每个节点的标签为自己的id*** 
	}
	//初始化邻接关系
	size_t edge_size = t_relation.size();
	for(unsigned int i = 0;i < edge_size;i++)
	{
		m_node_vec[m_relation_vec[i].first].neighbor.push_back(m_relation_vec[i].second);
        m_node_vec[m_relation_vec[i].second].neighbor.push_back(m_relation_vec[i].first);
	}
}