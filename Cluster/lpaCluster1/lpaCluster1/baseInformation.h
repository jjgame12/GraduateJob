#ifndef BASEINFORMATION_H
#define BASEINFORMATION_H

struct Node
{
	//int id;//存储节点的序号
	int label_size;//节点的标签数目
	unsigned int* label_content;//标签的实际值，若节点数目太大，标签也会很多，使用unsigned int

	//相邻节点id,通过节点id访问相邻节点信息,存储其id，表示偏移量，int占字节少，
	//若存指向邻居节点的指针，若是64位系统，则会加大空间冗余，增加内存占用量
	vector<unsigned int> neighbor;
};





#endif