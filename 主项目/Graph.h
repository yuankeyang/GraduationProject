#pragma once

#include <map>
#include <string>
#include "Vertex.h"

class Graph
{
public:
	Graph() = default;
	void insert_vertex(int);
	void insert_vertexes(int);
	void insert_vertexes(int, int);
	int get_vertex_number();
	void insert_edge(int, int);
	void insert_edge(int, int, float);
	void remove_edge(int, int);

	void print_graph() const;
	void read_adjacency_list(std::string);
	float get_weight(int, int);
	friend std::ostream& operator<<(std::ostream&, const Graph&);
protected:
	void insert_vertex(int, Vertex);
private:
	std::map<int, Vertex> vertexes;
};

void print_graph(const Graph&);