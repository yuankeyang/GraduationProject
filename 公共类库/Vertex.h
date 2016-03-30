#pragma once
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 1
#include <iterator>
#include <boost/unordered_map.hpp>
#include <vector>
#include "Edge.h"
typedef int VERTEXTYPE;
class Vertex
{
public:
	
	class ConstructionToken
	{
	private:
		ConstructionToken() = default;
		friend class Graph;
	};
	Vertex();
	Vertex(const ConstructionToken &);

	const std::vector<VERTEXTYPE> copy_edges() const;
	std::pair<boost::unordered_map<VERTEXTYPE, Edge>::iterator, bool> insert_edge(const VERTEXTYPE&);
	std::pair<boost::unordered_map<VERTEXTYPE, Edge>::iterator, bool> insert_edge(const VERTEXTYPE&, EDGE_DATE_TYPE& weight);
	void remove_edge(const VERTEXTYPE&);
	EDGE_DATE_TYPE get_weight(VERTEXTYPE&);
	int in_degree;
	int out_degree;
private:
	boost::unordered_map<VERTEXTYPE, Edge> edges;
	
};
