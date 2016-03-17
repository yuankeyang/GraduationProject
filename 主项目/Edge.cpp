#include "Edge.h"

Edge::ConstructionToken::ConstructionToken() = default;

Edge::Edge(const Edge &) = default;

Edge::Edge(const ConstructionToken &)
{
	set_weight(-1);
}

void Edge::set_weight(EDGE_DATE_TYPE w)
{
	weight = w;
}

EDGE_DATE_TYPE Edge::get_weight()
{
	return weight;
}