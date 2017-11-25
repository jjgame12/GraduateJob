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
	//��Ϣ��ʼ��
	initial(node_sum, t_relation);//��ǩ��ʼ�����д��Ż���Ŀǰֻ��һ����ǩ���ҳ�ʼ��ʱ���б�ǩ��ͬ����������Ż�
	m_type = type;

	//��ʼ����
	doRun(iter_times);

	//��ø�������������***�����ص������أ�
	//TODO:��ʱĬ��ÿ���ڵ�ı�ǩֻ��һ���ˣ�����ʵ�Ż��Ļ���һ��***
	vector<vector<unsigned int> > result;
	map<unsigned int, vector<unsigned int>*> result_map;//<��ǩ��, ͬһ��ǩ�Ľڵ�id> 

	//�����ڵ�����������ǩһ�µĽڵ��Ϊͳһһ������ţ�����������
	unsigned int* t_label = NULL;
	for(unsigned int i = 1;i <= m_node_sum;i++)
	{
		t_label = m_node_vec[i].label_content;
		if(result_map[t_label[0] ]  == NULL)
		{
			result_map[t_label[0] ] = new vector<int>;
		}
		result_map[t_label[0] ]->push_back(i);//���ڵ�id�����Ӧ�ı�ǩ��������
	}

	//ɾ���м���̲���Ҫ�ı���
	deleteTempVar();

}

void LpaCluster::doRun(int iter_times)
{
	//�м��������Ϊ������ʽڵ�˳��Ĳ���
	vector<unsigned int> random_order;
	random_order.resize(m_node_sum+1);
	for(unsigned int i = 1;i <= m_node_sum;i++)
	{
		random_order[i] = i;//���ո������е�Ԫ����Ϊ�ڵ��id���ﵽ����������ʽڵ��Ŀ��
	}
	
	if(m_type == 1)//ֻѡ��һ����ǩ����***
	{
		//��ʱ����
		unsigned int t_id = 1;//��ǰ���ʵĽڵ�id
		unsigned int t_neighbor_id = 0;//��ǰ���ʵĽڵ���ڽӽڵ�id
		int t_label_size = 1;
		unsigned int* t_neighbor_label_content = NULL;//��ǰ���ʵĽڵ���ھӽڵ�ı�ǩ��
		unsigned int max_label_times = -1;//��ǩ���ִ�����¼
		unsigned int max_label_content = 0;//�������ı�ǩ��

		//��ʼ����,��Ҫ��ʼ��������������ʲô��Ϊ������
		for(int t_iter = 0;t_iter < iter_times;t_iter++)
		{
			//������ҽڵ�˳��
			random_shuffle(random_order.begin(), random_order.end());//����Խڵ�id����,���մ�
			//˳����ʽڵ�

			//��ÿһ���ڵ㣬�����Χ�ڵ�ı�ǩ�������첽�ķ�ʽ���±�ǩ����������
			for(unsigned int i = 1;i <= m_node_sum;i++)
			{	
				max_label_times = -1;
				t_id = random_order[i];
				vector<unsigned int>& t_neighbor = m_node_vec[t_id].neighbor;

				//�п���û���ھӣ�û���ھ�������ʼ��ǩ��
				if(t_neighbor.empty())
				{
					continue;
				}

				//�����ھ�		
				//�Ե�ǰ�ڵ��ҵ��ٽ��ڵ�ı�ǩֵ���������Ǹ���ǩ
				map<unsigned int, unsigned int> t_label_map;//<��ǩ�ţ����ִ���>
				for(size_t neighbor_number = 0;neighbor_number < t_neighbor.size();neighbor_number++)
				{
					t_neighbor_id = t_neighbor[neighbor_number];
					t_neighbor_label_content = m_node_vec[t_neighbor_id].label_content;
					t_label_map[t_neighbor_label_content[0]]++;
				}

				for(map<unsigned int, unsigned int>::iterator it = t_label_map.begin();it != t_label_map.end();it++)
				{
					//������ͬ����Ŀ�ı�ǩ�����ȡ��? ���������ǩ��
					//TODO:�˴���Ȼ��ѡȡһ�����ֵ�����ж����ͬ��ǩ������ֻ��ѡһ������Ҫ�Ľ�***
					//�˴����ھӽڵ��ǰ���map�ĺ������˳��ȥ�����ұ�ǩ�������ֵ����ô�����
					//�����ǩ������һ����ֻ��ȡ����С�ı�ǩ�ŵı�ǩ***
					//��ζ��ھӽڵ�ı�ǩ��ͳ�ƽ���һ��������ʣ���map������ʣ�Ȼ��ȡ���ֵ
					//֮һ��***
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

void LpaCluster::deleteTempVar()
{
	if(m_type == 1)//ÿ���ڵ�ֻ������һ����ǩ�ĵ�ַ
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
