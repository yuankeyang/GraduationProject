#include <iostream>
#include "Graph.h"

int main(int argc, char* argv[])
{
	printf("毕业设计:社交网络中基于隐私保护的好友推荐算法\n");
	Graph g1(false);
	g1.read_adjacency_list_rel("facebook_combined.txt");
	std::cout << "无向图g1的节点个数：" << g1.get_vertex_number() << std::endl;
	std::cout << "无向图g1的边的个数：" << g1.get_edges() << std::endl;
	std::cout << "edge(0, 50)的weight是：" << g1.get_weight("0", "50") << std::endl;
	printf("d(4020, 4032) = %d\n", g1.bfs("4020", "4032"));
	printf("d(4032, 4020) = %d\n", g1.bfs("4032", "4020"));
	return 0;
}