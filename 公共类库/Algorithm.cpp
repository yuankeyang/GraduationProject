#include <iomanip>
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

SAMPLE Algorithm::offline_sample(VERTEXTYPE vertex)
{
	/*HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = 0;
	coord.Y = 9;*/
	SAMPLE sample_vertex;
	int vertexes = static_cast<int>(g.get_vertex_number());
	this->r = (int)floor(log2(vertexes));
	generate_seeds(this->r, vertexes);
	assert(seeds[0].size() == 1);
	for (int i = 0; i < r + 1; i++)
	{
		//For each node u, for all these sets Si, compute (wi, ��i)
		std::set<int>::iterator it = seeds[i].begin();
		VERTEXTYPE min_node = *it;
		int min = g.bfs(vertex, min_node);

		for (++it; it != seeds[i].end(); it++)
		{
			VERTEXTYPE node = *it;
			int distance = g.bfs(vertex, node);
			if (min > distance)
			{
				min = distance;
				min_node = node;
			}
		}
		D* d = new D(min_node, min);
		/*std::string str = "d";
		str.append(std::to_string(i));
		str.append("(");
		str.append(std::to_string(min_node));
		str.append(", ");
		str.append(std::to_string(min));
		str.append(")");
		SetConsoleCursorPosition(hConsole, coord);
		std::cout << std::left << std::setw(20) << str;*/
		sample_vertex.push_back(*d);
	}
	return sample_vertex;
}

SAMPLE Algorithm::offline_sketch()
{
	return SAMPLE();
}

DISTANCE Algorithm::online_common_seed(VERTEXTYPE u, VERTEXTYPE v)
{
	return DISTANCE();
}

std::string Algorithm::sample_to_string(SAMPLE& sample)
{
	std::string str = "";
	for (SAMPLE::iterator it = sample.begin(); it != sample.end(); it++)
	{
		str.append(std::to_string((*it).first));
		str.append(",");
		str.append(std::to_string((*it).second));
		str.append(" ");
	}
	str.append("\n");
	return str;
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
		//���ȷֲ�
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(0, vertexes - 1);
		for (int j = 0; j < e; j++)
		{
			seeds[i].insert(distribution(generator));
		}
	}
}
