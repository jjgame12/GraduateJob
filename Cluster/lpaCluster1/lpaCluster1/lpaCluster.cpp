#include "lpaCluster.h"

#include <iostream>
#include <vector>
#include <map>


LpaCluster::LpaCluster(unsigned int node_sum, vector<pair<unsigned int, unsigned int> >& t_relation)
{	
	
}

LpaCluster::~LpaCluster()
{
	
}

vector<vector<unsigned int> > LpaCluster::getCluster(unsigned int node_sum, 
													 vector<pair<unsigned int, unsigned int> >& t_relation, 
													 int iter_times,
													 int type = 1)
{
	//信息初始化
	initial(node_sum, t_relation);//标签初始化，有待优化，目前只用一个标签，且初始化时所有标签不同，可针对性优化
	m_type = type;

	//开始迭代
	doRun(iter_times);

	//获得各个独立的社团***想获得重叠社团呢？
	//TODO:此时默认每个节点的标签只有一个了，但其实优化的话不一定***
	vector<vector<unsigned int> > result;
	map<unsigned int, vector<unsigned int>*> result_map;//<标签号, 同一标签的节点id> 

	//遍历节点容器，将标签一致的节点归为统一一类的社团，并返回社团
	unsigned int* t_label = NULL;
	for(unsigned int i = 1;i <= m_node_sum;i++)
	{
		t_label = m_node_vec[i].label_content;
		if(result_map[t_label[0] ]  == NULL)
		{
			result_map[t_label[0] ] = new vector<int>;
		}
		result_map[t_label[0] ]->push_back(i);//将节点id放入对应的标签号容器中
	}

	//删除中间过程不需要的变量
	deleteTempVar();

}

void LpaCluster::doRun(int iter_times)
{
	//中间变量，作为随机访问节点顺序的参照
	vector<unsigned int> random_order;
	random_order.resize(m_node_sum+1);
	for(unsigned int i = 1;i <= m_node_sum;i++)
	{
		random_order[i] = i;//按照该容器中的元素作为节点的id来达到后续随机访问节点的目的
	}
	
	if(m_type == 1)//只选择一个标签保留***
	{
		//临时变量
		unsigned int t_id = 1;//当前访问的节点id
		unsigned int t_neighbor_id = 0;//当前访问的节点的邻接节点id
		int t_label_size = 1;
		unsigned int* t_neighbor_label_content = NULL;//当前访问的节点的邻居节点的标签号
		unsigned int max_label_times = -1;//标签出现次数记录
		unsigned int max_label_content = 0;//出现最多的标签号

		//开始迭代,需要初始化迭代次数吗？以什么作为结束？
		for(int t_iter = 0;t_iter < iter_times;t_iter++)
		{
			//随机打乱节点顺序
			random_shuffle(random_order.begin(), random_order.end());//随机对节点id排序,按照此
			//顺序访问节点

			//对每一个节点，检查周围节点的标签，采用异步的方式更新标签，快速收敛
			for(unsigned int i = 1;i <= m_node_sum;i++)
			{	
				max_label_times = -1;
				t_id = random_order[i];
				vector<unsigned int>& t_neighbor = m_node_vec[t_id].neighbor;

				//有可能没有邻居，没有邻居则保留初始标签号
				if(t_neighbor.empty())
				{
					continue;
				}

				//若有邻居		
				//对当前节点找到临近节点的标签值数量最大的那个标签
				map<unsigned int, unsigned int> t_label_map;//<标签号，出现次数>
				for(size_t neighbor_number = 0;neighbor_number < t_neighbor.size();neighbor_number++)
				{
					t_neighbor_id = t_neighbor[neighbor_number];
					t_neighbor_label_content = m_node_vec[t_neighbor_id].label_content;
					t_label_map[t_neighbor_label_content[0]]++;
				}

				for(map<unsigned int, unsigned int>::iterator it = t_label_map.begin();it != t_label_map.end();it++)
				{
					//若有相同的数目的标签，如何取舍? 保留多个标签？
					//TODO:此处依然是选取一个最大值，若有多个相同标签数，则只会选一个，需要改进***
					//此处对邻居节点是按照map的红黑树的顺序去遍历找标签数的最大值，那么如果有
					//多个标签的数量一样，只会取到最小的标签号的标签***
					//如何对邻居节点的标签数统计进行一个随机访问？对map随机访问？然后取最大值
					//之一？***
					if(it->second > max_label_times)
					{
						max_label_times = it->second;
						max_label_content = it->first;
					}
				}

				m_node_vec[t_id].label_content[0] = max_label_content;
				t_neighbor_label_content = NULL;
			}
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

void LpaCluster::deleteTempVar()
{
	if(m_type == 1)//每个节点只申请了一个标签的地址
	{
		for(unsigned int i = 1;i <= m_node_sum;i++)
		{
			if(m_node_vec[i].label_content != NULL)
			{
				delete m_node_vec[i].label_content;
				m_node_vec[i].label_content = NULL;
			}
		}

		if(m_node_vec != NULL)
		{
			delete[] m_node_vec;
			m_node_vec = NULL;
		}
	}
}
