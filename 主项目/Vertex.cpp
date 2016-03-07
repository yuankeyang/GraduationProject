#include <vector>
#include <utility>
#include "Vertex.h"
#include "Edge.h"

using edge_pair = std::pair<int, Edge>;

Vertex::Vertex(const ConstructionToken &)
{
}

void Vertex::insert_edge(const int & end_point)
{
	Edge new_edge{ Edge::ConstructionToken{} };
	edge_pair temp(end_point, new_edge);
	edges.insert(temp);
}

void Vertex::insert_edge(const int & end_point, float weight)
{
	Edge new_edge{ Edge::ConstructionToken{} };
	new_edge.set_weight(weight);
	edge_pair temp(end_point, new_edge);
	edges.insert(temp);
}

void Vertex::remove_edge(const int & edge)
{
	edges.erase(edge);
}

const std::vector<int> Vertex::copy_edges() const
{
	std::vector<int> keys;
	for (auto& pair : edges)
	{
		keys.push_back(pair.first);
	}
	return keys;
}

float Vertex::get_weight(int v)
{
	auto it = edges.find(v);
	if (it == edges.end())
		return -1;
	return it->second.get_weight();

}