/*
*
*/
#pragma once
#include <iostream>
#include <set>
#include <cassert>
#include <cmath>
#include <random>
#include "Graph.h"
typedef std::pair<VERTEXTYPE, int> D;
typedef std::vector<D> SAMPLE;
typedef int DISTANCE;
class Algorithm
{
public:
	Algorithm(Graph g);
	~Algorithm();
	
	SAMPLE offline_sample(VERTEXTYPE vertex);
	std::string sample_to_string(SAMPLE& sample);
private:
	void generate_seeds(int r, int vertexes);
private:
	std::set<int>* seeds;
	int r;
	Graph g;
};

