#pragma once
#include <boost/unordered_map.hpp>
#include <string>
#include "Vertex.h"

class Graph
{
public:
	typedef boost::unordered_map<VERTEXTYPE, Vertex>::iterator ITR;
	Graph();
	Graph(bool is_directed);
	void insert_vertex(VERTEXTYPE&);
	std::size_t get_vertex_number();
	void insert_edge(VERTEXTYPE&, VERTEXTYPE&);
	void insert_edge(VERTEXTYPE&, VERTEXTYPE&, EDGE_DATE_TYPE& weight);
	void remove_edge(VERTEXTYPE&, VERTEXTYPE&);

	void print_graph() const;
	//读取邻接表
	void read_adjacency_list_rel(std::string&);
	EDGE_DATE_TYPE get_weight(VERTEXTYPE&, VERTEXTYPE&);
	friend std::ostream& operator<<(std::ostream&, const Graph&);
	//宽度优先算法
	EDGE_DATE_TYPE bfs(VERTEXTYPE& from, VERTEXTYPE& to);
	//获取边数
	int get_edges();
	//迭代器
	ITR begin();
	ITR end();
	//如果是无向图的话，度为in_degree + out_degree
	int get_in_degree(VERTEXTYPE& v);
	int get_out_degree(VERTEXTYPE& v);

protected:
	void insert_vertex(VERTEXTYPE&, Vertex&);
private:
	boost::unordered_map<VERTEXTYPE, Vertex> vertexes;
	long int edges;
	bool directed;
};

void print_graph(const Graph&);