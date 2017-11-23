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
	initial();//��ǩ��ʼ�����д��Ż���Ŀǰֻ��һ����ǩ���ҳ�ʼ��ʱ���б�ǩ��ͬ����������Ż�

	//��ʼ����
	doRun(iter_times);

	//�����ڵ�����������ǩһ�µĽڵ��Ϊͳһһ������ţ�����������

}

void LpaCluster::doRun(int iter_times, int type)
{
	//�м��������Ϊ������ʽڵ�˳��Ĳ���
	vector<unsigned int> random_order;
	random_order.resize(m_node_sum+1);
	for(unsigned int i = 1;i <= m_node_sum;i++)
	{
		random_order[i] = i;//���ո������е�Ԫ����Ϊ�ڵ��id���ﵽ����������ʽڵ��Ŀ��
	}
	
	if(type == 1)//ֻѡ��һ����ǩ����***
	{
		//��ʱ����
		unsigned int t_id = 1;//��ǰ���ʵĽڵ�id
		int t_label_size = 1;
		unsigned int* t_label_content = NULL;

		//��ʼ����,��Ҫ��ʼ��������������ʲô��Ϊ������
		for(int t_iter = 0;t_iter < iter_times;t_iter++)
		{
			//������ҽڵ�˳��
			random_shuffle(random_order.begin(), random_order.end());//����Խڵ�id����,���մ�
			//˳����ʽڵ�

			//��ÿһ���ڵ㣬�����Χ�ڵ�ı�ǩ�������첽�ķ�ʽ���±�ǩ����������
			for(unsigned int i = 1;i <= m_node_sum;i++)
			{
				t_id = random_order[i];
				vector<unsigned int>& t_neighbor = m_node_vec[t_id].neighbor;

				//�Ե�ǰ�ڵ��ҵ��ٽ��ڵ�ı�ǩֵ���������Ǹ���ǩ
				map<unsigned int, unsigned int> t_label_map;
				for(size_t neighbor_number = 0;neighbor_number < t_neighbor.size();neighbor_number++)
				{
					t_label_map[t_neighbor[neighbor_number]]++;
				}
				

			}

			//������ͬ����Ŀ�ı�ǩ�����ȡ��? ���������ǩ��

		}
	}
	

}

void LpaCluster::initial(unsigned int node_sum, vector<pair<unsigned int, unsigned int> >& t_relation)
{
	m_relation_vec = t_relation;

	m_node_sum = node_sum;
	//��ʼ���ڵ�ṹ
	m_node_vec = new Node[node_sum+1];//m_node_vec�ı�Ŵ���ÿһ���ڵ��id��m_node_vec[0]�������κνڵ�
    
	//��ʼ���ڵ��ǩ
	for(unsigned int i = 1;i <= node_sum;i++)
	{
		m_node_vec[i].label_size = 1;//��ʱ�趨��ǩ��ĿΪ1***
		m_node_vec[i].label_content = new unsigned int(i);//����ʼ��ÿ���ڵ�ı�ǩΪ�Լ���id*** 
	}
	//��ʼ���ڽӹ�ϵ
	size_t edge_size = t_relation.size();
	for(unsigned int i = 0;i < edge_size;i++)
	{
		m_node_vec[m_relation_vec[i].first].neighbor.push_back(m_relation_vec[i].second);
        m_node_vec[m_relation_vec[i].second].neighbor.push_back(m_relation_vec[i].first);
	}
}