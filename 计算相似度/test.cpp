#include <iostream>
#include <Graph.h>

int main(int argc, char* argv[])
{
	//����ͼ
	Graph g(false);
	int v1 = 0;
	int v2 = 1;
	int v3 = 2;
	int v4 = 3;
	int v5 = 4;
	g.insert_edge(v1, v2);
	g.insert_edge(v1, v3);
	g.insert_edge(v1, v4);
	g.insert_edge(v1, v5);
	g.insert_edge(v3, v2);
	g.insert_edge(v4, v2);
	g.insert_edge(v5, v2);
	g.insert_edge(v5, v4);
	std::cout << "��������" << g.get_vertex_number() << std::endl;
	std::cout << "�߸�����" << g.get_edges() << std::endl;
	std::cout << "���v5�Ķ�" << g.get_out_degree(v5) + g.get_in_degree(v5) << std::endl;
	return EXIT_SUCCESS;
}