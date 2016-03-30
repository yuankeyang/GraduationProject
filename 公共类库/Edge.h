#pragma once

typedef int EDGE_DATE_TYPE;

class Edge
{
public:
	class ConstructionToken
	{
	private:
		ConstructionToken();
		friend class Vertex;
	};

	Edge(const Edge &);
	Edge(const ConstructionToken &);

	void set_weight(EDGE_DATE_TYPE);
	EDGE_DATE_TYPE get_weight();
private:
	EDGE_DATE_TYPE weight;
};
