#pragma once
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 1
#include <iterator>
#include <boost/unordered_map.hpp>
#include <vector>
#include "Edge.h"

class Vertex
{
public:
	class ConstructionToken
	{
	private:
		ConstructionToken() = default;
		friend class Graph;
	};

	Vertex(const ConstructionToken &);

	const std::vector<std::string> copy_edges() const;
	std::pair<boost::unordered_map<std::string, Edge>::iterator, bool> insert_edge(const std::string&);
	std::pair<boost::unordered_map<std::string, Edge>::iterator, bool> insert_edge(const std::string&, EDGE_DATE_TYPE& weight);
	void remove_edge(const std::string&);
	EDGE_DATE_TYPE get_weight(std::string&);
private:
	boost::unordered_map<std::string, Edge> edges;
};
