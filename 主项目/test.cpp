#include <iostream>
#include "Graph.h"

int main()
{
	Graph g;

	//g.insert_vertex(1);
	//g.insert_vertex(2);
	//g.insert_vertex(3);
	//g.insert_vertex(4);

	//g.insert_edge(1, 2, 0.1f);
	//g.insert_edge(1, 3, 0.2f);
	//g.insert_edge(1, 4, 1.3f);
	//g.insert_edge(2, 4, 1.5f);
	//g.insert_edge(3, 2, 3.7f);
	//g.insert_edge(1, 1, 6.9f);

	//g.print_graph();
	//std::cout << std::endl << "Vertex number is: " << g.get_vertex_number() 
	//	<< std::endl;
	//std::cout << "Vertex 1 to Vertex 2 is " << g.get_weight(1, 2) << std::endl;
	//std::cout << "Vertex 1 to Vertex 3 is " << g.get_weight(1, 3) << std::endl;
	//std::cout << "Vertex 2 to Vertex 4 is " << g.get_weight(2, 4) << std::endl;
	//std::cout << "Vertex 3 to Vertex 2 is " << g.get_weight(3, 2) << std::endl;
	//std::cout << "Vertex 1 to Vertex 1 is " << g.get_weight(1, 1) << std::endl;
	//std::cout << "Vertex 2 to Vertex 3 is " << g.get_weight(2, 3) << std::endl;

	//g.insert_edge(5, 4);
	//std::cout << g;
	//std::cout << std::endl;
	//g.remove_edge(5, 4);
	//g.insert_vertexes(9);
	//print_graph(g);
	//std::cout << std::endl << "Vertex number is: " << g.get_vertex_number()
	//	<< std::endl;
	//std::cout << "Vertex 7 to Vertex 3 is " << g.get_weight(7, 3) << std::endl;
	//
	g.read_adjacency_list("test.adjlist");
	g.print_graph();
	std::cout << "Vertex number is: " << g.get_vertex_number() << std::endl;
	g.remove_edge(98,99);
	g.print_graph();
	return 0;
}