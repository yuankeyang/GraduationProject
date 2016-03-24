#pragma once

#include <map>
#include <string>
#include "Vertex.h"

class Graph
{
public:
	typedef std::map<std::string, Vertex>::iterator ITR;
	Graph();
	Graph(bool is_directed);
	void insert_vertex(std::string);
	int get_vertex_number();
	void insert_edge(std::string, std::string);
	void insert_edge(std::string, std::string, EDGE_DATE_TYPE weight);
	void remove_edge(std::string, std::string);

	void print_graph() const;
	//��ȡ�ڽӱ�
	void read_adjacency_list_rel(std::string);
	EDGE_DATE_TYPE get_weight(std::string, std::string);
	friend std::ostream& operator<<(std::ostream&, const Graph&);
	//��������㷨
	EDGE_DATE_TYPE bfs(std::string from, std::string to);
	//��ȡ����
	int get_edges();
	//������
	ITR begin();
	ITR end();
protected:
	void insert_vertex(std::string, Vertex);
private:
	std::map<std::string, Vertex> vertexes;
	long int edges;
	bool directed;
};

void print_graph(const Graph&);