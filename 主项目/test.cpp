#include <iostream>
#include "Graph.h"

int main(int argc, char* argv[])
{
	printf("��ҵ���:�罻�����л�����˽�����ĺ����Ƽ��㷨\n");
	Graph g1(false);
	g1.read_adjacency_list_rel("facebook_combined.txt");
	std::cout << "����ͼg1�Ľڵ������" << g1.get_vertex_number() << std::endl;
	std::cout << "����ͼg1�ıߵĸ�����" << g1.get_edges() << std::endl;
	std::cout << "edge(0, 50)��weight�ǣ�" << g1.get_weight("0", "50") << std::endl;
	printf("d(4020, 4032) = %d\n", g1.bfs("4020", "4032"));
	printf("d(4032, 4020) = %d\n", g1.bfs("4032", "4020"));
	return 0;
}