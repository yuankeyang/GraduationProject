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
	//��ȡ�ڽӱ�
	void read_adjacency_list_rel(std::string&);
	EDGE_DATE_TYPE get_weight(VERTEXTYPE&, VERTEXTYPE&);
	friend std::ostream& operator<<(std::ostream&, const Graph&);
	//��������㷨
	EDGE_DATE_TYPE bfs(VERTEXTYPE& from, VERTEXTYPE& to);
	//��ȡ����
	int get_edges();
	//������
	ITR begin();
	ITR end();
	//���������ͼ�Ļ�����Ϊin_degree + out_degree
	int get_in_degree(VERTEXTYPE& v);
	int get_out_degree(VERTEXTYPE& v);
	bool is_directed();
protected:
	void insert_vertex(VERTEXTYPE&, Vertex&);
private:
	boost::unordered_map<VERTEXTYPE, Vertex> vertexes;
	long int edges;
	bool directed;
};
void print_graph(const Graph&);