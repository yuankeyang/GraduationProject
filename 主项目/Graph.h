#pragma once

#include <map>
#include <string>
#include "Vertex.h"

class Graph
{
public:
	Graph() = default;
	void insert_vertex(std::string);
	int get_vertex_number();
	void insert_edge(std::string, std::string);
	void insert_edge(std::string, std::string, float);
	void remove_edge(std::string, std::string);

	void print_graph() const;
	void read_adjacency_list(std::string);
	float get_weight(std::string, std::string);
	friend std::ostream& operator<<(std::ostream&, const Graph&);
	void bfs(std::string from, std::string to);
protected:
	void insert_vertex(std::string, Vertex);
private:
	std::map<std::string, Vertex> vertexes;
};

void print_graph(const Graph&);