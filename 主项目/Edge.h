#pragma once


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

	void set_weight(float);
	float get_weight();
private:
	float weight;
};
