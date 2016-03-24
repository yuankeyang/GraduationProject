#include <iostream>
#include <fstream>
#include "Graph.h"
#include "Algorithm.h"

int main(int argc, char* argv[])
{
	std::string data_file = "test1.adjlist";
	std::string sketch_file = "test1_sketch.txt";
	printf("��ҵ���:�罻�����л�����˽�����ĺ����Ƽ��㷨\n");
	Graph g1(false);
	g1.read_adjacency_list_rel(data_file);
	std::cout << "����ͼg1�Ľڵ������" << g1.get_vertex_number() << std::endl;
	std::cout << "����ͼg1�ıߵĸ�����" << g1.get_edges() << std::endl;
	Algorithm al(g1);
	std::ofstream ofs;
	ofs.open(sketch_file);
	if (ofs.is_open())
	{
		ofs.clear();
		for (Graph::ITR it = g1.begin(); it != g1.end(); it++) {
			std::string node = (*it).first;
			SAMPLE sample = al.offline_sample(node);
			ofs << node;
			ofs << al.sample_to_string(sample);
		}
		ofs.close();
	}
	else 
	{
		std::cout << "�ļ�" << sketch_file << "�򿪴���" << std::endl;
		ofs.close();
		return 0;
	}
	return 0;
}