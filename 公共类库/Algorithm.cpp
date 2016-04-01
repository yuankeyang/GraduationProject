#include <iomanip>
#include "Algorithm.h"
#include <cmath>

Algorithm::Algorithm(Graph g)
{
	seeds = NULL;
	r = 0;
	this->g = g;
	int vertexes = static_cast<int>(g.get_vertex_number());
	this->r = (int)floor(log2(vertexes));
	generate_seeds(this->r, vertexes);
	assert(seeds[0].size() == 1);
}

Algorithm::Algorithm()
{
}


Algorithm::~Algorithm()
{
}

SAMPLE Algorithm::offline_sample(VERTEXTYPE vertex)
{
	SAMPLE sample_vertex;
	
	for (int i = 0; i < r + 1; i++)
	{
		//For each node u, for all these sets Si, compute (wi, δi)
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
		sample_vertex.push_back(*d);
	}
	return sample_vertex;
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
/*读取sketchs文件*/
void Algorithm::read_sketchs(std::string & file)
{
	std::cout << "读取SKETCH文件\n";
	std::ifstream ifs(file);
	std::string str;
	while (std::getline(ifs, str))
	{
		if (str.at(0) == '#')
		{
			continue;
		}
		std::vector<std::string> elems = Helper::split(str, ' ');
		const int size = static_cast<int>(elems.size());
		if (size > 0)
		{
			VERTEXTYPE node = std::stoi(elems[0]);
			SAMPLE sketch;
			for (int i = 1; i < size; i++)
			{
				std::vector<std::string> data = Helper::split(elems[i], ',');
				const int data_size = static_cast<int>(data.size());
				assert(data_size == 2);
				VERTEXTYPE v = std::stoi(data[0]);
				int distance = std::stoi(data[1]);
				D* d = new D(v, distance);
				sketch.push_back(*d);
			}
			assert(sketch.size() > 0);
			std::pair<VERTEXTYPE, SAMPLE> node_sample(node, sketch);
			map.insert(node_sample);
			std::cout << "\rReading vertex:" << node;
		}
	}
	std::cout << "\r---------------------\n";
	std::cout << "读取完毕！" << std::endl;
	std::cout << "结点个数:" << map.size() << std::endl;
}
/*估计两个结点间的距离*/
int Algorithm::estimate_distance(VERTEXTYPE v, VERTEXTYPE u)
{
	//两个节点相同的话距离0
	if (v == u)
		return 0;

	SAMPLE& v_sketch = map[v];
	SAMPLE& u_sketch = map[u];
	boost::unordered_map<VERTEXTYPE, int> map;
	for (int i = 0; i < u_sketch.size(); i++)
	{
		map.insert(u_sketch[i]);
	}
	int distance = -1;
	for (int i = 0; i < v_sketch.size(); i++)
	{
		VERTEXTYPE node = v_sketch[i].first;
		auto itr = map.find(node);
		int dist = 0;
		if (itr != map.end())
		{
			dist = v_sketch[i].second + itr->second;
			if (distance == -1)
				distance = dist;
			else
				distance = (distance < dist) ? distance : dist;
		}
	}
	return distance;
}
/*生成种子集合*/
void Algorithm::generate_seeds(int r, int vertexes)
{
	assert(r > 0);
	assert(vertexes > 0);
	assert(this->r > 0);
	seeds = new std::set<int>[r + 1];
	for (int i = 0; i <= r; i++)
	{
		int e = (int)exp2l(i);
		//均匀分布
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(0, vertexes - 1);
		for (int j = 0; j < e; j++)
		{
			int s = 0;
			int degree = 0;
			do
			{
				s = distribution(generator);
				degree = g.get_in_degree(s) + g.get_out_degree(s);
			} while (degree < 2);
			seeds[i].insert(s);
		}
	}
}

boost::unordered_map<VERTEXTYPE,SAMPLE>::iterator Algorithm::get_map_begin()
{
	return map.begin();
}

boost::unordered_map<VERTEXTYPE, SAMPLE>::iterator Algorithm::get_map_end()
{
	return map.end();
}

double Algorithm::calculate_closeness(VERTEXTYPE v, VERTEXTYPE u)
{
	//两个节点相同的话相似度为1
	if (v == u)
		return 0;

	SAMPLE v_sketch = map[v];
	SAMPLE u_sketch = map[u];
	int closeness = 0;
	int sketch_size = static_cast<int>(v_sketch.size());
	for (int i = 0; i < sketch_size; i++)
	{
		int temp = v_sketch[i].second - u_sketch[i].second;
		closeness += abs(temp);
		int dist = estimate_distance(v_sketch[i].first, u_sketch[i].first);
		if (dist == -1)
			closeness = -1;
		else
			closeness += dist;
	}
	if (sketch_size == 0)
		throw std::overflow_error("除零异常");
	return closeness/sketch_size;
}

std::set<CLOSENESS, Algorithm::cmpStruct> Algorithm::get_recommend(VERTEXTYPE & node)
{
	std::set<CLOSENESS, cmpStruct> set;
	if (map.find(node) == map.end())
		return set;

	for (auto itr = map.begin(); itr != map.end(); itr++)
	{
		double closeness = calculate_closeness(node, itr->first);
		CLOSENESS temp(itr->first, closeness);
		set.insert(temp);
	}
	assert(set.size() > 0);
	return set;
}
