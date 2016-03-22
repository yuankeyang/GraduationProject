#include "Algorithm.h"


Algorithm::Algorithm(Graph g)
{
	seeds = NULL;
	r = 0;
	this->g = g;
}


Algorithm::~Algorithm()
{
}

SAMPLE Algorithm::offline_sample(std::string vertex)
{
	SAMPLE sample_vertex;
	int vertexes = g.get_vertex_number();
	this->r = (int)floor(log2(vertexes));
	generate_seeds(this->r, vertexes);
	for (int i = 1; i < r + 1; i++)
	{
		//For each node u, for all these sets Si, compute (wi, ¦Äi)
		assert(seeds[0].size() == 1);
		std::string min_node = std::to_string(*seeds[0].begin());
		int min = g.bfs(vertex, min_node);
		for (int item : seeds[i])
		{
			std::string node = std::to_string(item);
			int distance = g.bfs(vertex, node);
			if (min > distance)
			{
				min = distance;
				min_node = node;
			}
		}
		D* d = new D(min, min_node);
		sample_vertex.insert(*d);
	}
	return sample_vertex;
}

SAMPLE Algorithm::offline_sketch()
{
	return SAMPLE();
}

DISTANCE Algorithm::online_common_seed(std::string u, std::string v)
{
	return DISTANCE();
}

void Algorithm::generate_seeds(int r, int vertexes)
{
	assert(r > 0);
	assert(vertexes > 0);
	assert(this->r > 0);
	seeds = new std::set<int>[r + 1];
	for (int i = 0; i <= r; i++)
	{
		int e = (int)exp2l(i);
		//¾ùÔÈ·Ö²¼
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(0, vertexes - 1);
		for (int j = 0; j < e; j++)
		{
			seeds[i].insert(distribution(generator));
		}
	}
}
