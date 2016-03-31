/*
*
*/
#pragma once
#include <iostream>
#include <set>
#include <cassert>
#include <cmath>
#include <random>
#include <fstream>
#include "Graph.h"
#include "Helper.h"

typedef std::pair<VERTEXTYPE, int> D;
typedef std::vector<D> SAMPLE;
typedef int DISTANCE;
typedef std::pair<VERTEXTYPE, double> CLOSENESS;
class Algorithm
{
public:
	Algorithm(Graph g);
	Algorithm();
	~Algorithm();
	
	SAMPLE offline_sample(VERTEXTYPE vertex);
	std::string sample_to_string(SAMPLE& sample);
	void read_sketchs(std::string &file);
	int estimate_distance(VERTEXTYPE v, VERTEXTYPE u);
private:
	void generate_seeds(int r, int vertexes);
private:
	std::set<int>* seeds;
	int r;
	Graph g;
	
	boost::unordered_map<VERTEXTYPE, SAMPLE> map;
public:
	//相似度比较结构体
	struct cmpStruct
	{
		bool operator() (const CLOSENESS& lhs, const CLOSENESS& rhs) const
		{
			return lhs.second < rhs.second;
		}
	};
	//迭代器
	boost::unordered_map<VERTEXTYPE, SAMPLE>::iterator get_map_begin();
	boost::unordered_map<VERTEXTYPE, SAMPLE>::iterator get_map_end();
	//计算相似度closeness[0,1]	1表示完全想似,0表示完全不同
	double calculate_closeness(VERTEXTYPE v, VERTEXTYPE u);
	std::set<CLOSENESS, cmpStruct> get_recommend(VERTEXTYPE& node);
};

