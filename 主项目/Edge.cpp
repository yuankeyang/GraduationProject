#include "Edge.h"

Edge::ConstructionToken::ConstructionToken() = default;

Edge::Edge(const Edge &) = default;

Edge::Edge(const ConstructionToken &)
{
	set_weight(-1);
}

void Edge::set_weight(float w)
{
	weight = w;
}

float Edge::get_weight()
{
	return weight;
}