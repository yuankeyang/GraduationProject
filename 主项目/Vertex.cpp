#include <vector>
#include <utility>
#include "Vertex.h"
#include "Edge.h"

using edge_pair = std::pair<VERTEXTYPE, Edge>;

Vertex::Vertex()
{
	in_degree = 0;
	out_degree = 0;
}

Vertex::Vertex(const ConstructionToken &)
{
	in_degree = 0;
	out_degree = 0;
}

std::pair<boost::unordered_map<VERTEXTYPE, Edge>::iterator, bool> Vertex::insert_edge(const VERTEXTYPE & end_point)
{
	Edge new_edge{ Edge::ConstructionToken{} };
	edge_pair temp(end_point, new_edge);
	return edges.insert(temp);
}

std::pair<boost::unordered_map<VERTEXTYPE, Edge>::iterator, bool> Vertex::insert_edge(const VERTEXTYPE & end_point, EDGE_DATE_TYPE& weight)
{
	Edge new_edge{ Edge::ConstructionToken{} };
	new_edge.set_weight(weight);
	edge_pair temp(end_point, new_edge);
	return edges.insert(temp);
}

void Vertex::remove_edge(const VERTEXTYPE & edge)
{
	edges.erase(edge);
}

const std::vector<VERTEXTYPE> Vertex::copy_edges() const
{
	std::vector<VERTEXTYPE> keys;
	for (auto& pair : edges)
	{
		keys.push_back(pair.first);
	}
	return keys;
}

EDGE_DATE_TYPE Vertex::get_weight(VERTEXTYPE& v)
{
	auto it = edges.find(v);
	if (it == edges.end())
		return -1;
	return it->second.get_weight();

}
