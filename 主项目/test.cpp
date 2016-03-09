#include <iostream>
#include "Graph.h"

int main()
{
	Graph g;

	g.insert_vertex("1");
	g.insert_vertex("2");
	g.insert_vertex("3");
	g.insert_vertex("4");

	g.insert_edge("1", "2", 0.1f);
	g.insert_edge("1", "3", 0.2f);
	g.insert_edge("1", "4", 1.3f);
	g.insert_edge("2", "4", 1.5f);
	g.insert_edge("3", "2", 3.7f);
	g.insert_edge("4", "5", 0.3f);
	g.insert_edge("5", "6", 6.9f);
	g.insert_edge("5", "7", 6.9f);
	g.insert_edge("7", "9", 6.9f);
	g.insert_edge("10", "9", 6.9f);
	g.insert_edge("7", "8", 6.9f);

	g.print_graph();
	std::cout << "图g的节点个数：" << g.get_vertex_number() << std::endl;
	g.bfs("1", "8");
	std::cout << "\n\n";
	Graph g1;
	g1.read_adjacency_list("test1.adjlist");
	g1.print_graph();
	std::cout << "图g1的节点个数：" << g1.get_vertex_number() << std::endl;
	g1.bfs("Barbadori","Pazzi");
	return 0;
}