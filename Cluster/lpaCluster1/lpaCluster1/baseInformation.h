#ifndef BASEINFORMATION_H
#define BASEINFORMATION_H

struct Node
{
	//int id;//�洢�ڵ�����
	int label_size;//�ڵ�ı�ǩ��Ŀ
	unsigned int* label_content;//��ǩ��ʵ��ֵ�����ڵ���Ŀ̫�󣬱�ǩҲ��ܶ࣬ʹ��unsigned int

	//���ڽڵ�id,ͨ���ڵ�id�������ڽڵ���Ϣ,�洢��id����ʾƫ������intռ�ֽ��٣�
	//����ָ���ھӽڵ��ָ�룬����64λϵͳ�����Ӵ�ռ����࣬�����ڴ�ռ����
	vector<unsigned int> neighbor;
};





#endif