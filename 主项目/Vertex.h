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

	const std::vector<int> copy_edges() const;
	void insert_edge(const int&);
	void insert_edge(const int&, float weight);
	void remove_edge(const int&);
	float get_weight(int);
private:
	std::map<int, Edge> edges;
};
