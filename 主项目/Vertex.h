#pragma once

#include <iterator>
#include <map>
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
	std::pair<std::map<std::string, Edge>::iterator, bool> insert_edge(const std::string&);
	std::pair<std::map<std::string, Edge>::iterator, bool> insert_edge(const std::string&, EDGE_DATE_TYPE weight);
	void remove_edge(const std::string&);
	EDGE_DATE_TYPE get_weight(std::string);
private:
	std::map<std::string, Edge> edges;
};
