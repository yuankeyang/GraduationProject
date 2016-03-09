#include <vector>
#include <utility>
#include "Vertex.h"
#include "Edge.h"

using edge_pair = std::pair<std::string, Edge>;

Vertex::Vertex(const ConstructionToken &)
{
}

void Vertex::insert_edge(const std::string & end_point)
{
	Edge new_edge{ Edge::ConstructionToken{} };
	edge_pair temp(end_point, new_edge);
	edges.insert(temp);
}

void Vertex::insert_edge(const std::string & end_point, float weight)
{
	Edge new_edge{ Edge::ConstructionToken{} };
	new_edge.set_weight(weight);
	edge_pair temp(end_point, new_edge);
	edges.insert(temp);
}

void Vertex::remove_edge(const std::string & edge)
{
	edges.erase(edge);
}

const std::vector<std::string> Vertex::copy_edges() const
{
	std::vector<std::string> keys;
	for (auto& pair : edges)
	{
		keys.push_back(pair.first);
	}
	return keys;
}

float Vertex::get_weight(std::string v)
{
	auto it = edges.find(v);
	if (it == edges.end())
		return -1;
	return it->second.get_weight();

}
