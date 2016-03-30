#include <iostream>
#include <Graph.h>

int main(int argc, char* argv[])
{
	//无向图
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
	std::cout << "结点个数：" << g.get_vertex_number() << std::endl;
	std::cout << "边个数：" << g.get_edges() << std::endl;
	std::cout << "结点v5的度" << g.get_out_degree(v5) + g.get_in_degree(v5) << std::endl;
	return EXIT_SUCCESS;
}