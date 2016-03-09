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
	void insert_edge(const std::string&);
	void insert_edge(const std::string&, float weight);
	void remove_edge(const std::string&);
	float get_weight(std::string);
private:
	std::map<std::string, Edge> edges;
};
