#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <fstream>
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Helper.h"

void Graph::insert_vertex(int id)
{
	Vertex::ConstructionToken c;
	Vertex v{ c };
	insert_vertex(id, v);
}

void Graph::insert_vertexes(int n)
{
	if (n < 0)
	{
		std::cout << "error:参数不合法（参数应该为大于0的整数）" << std::endl;
		return;
	}
	for (int i = 0; i <= n; i++)
	{
		Vertex::ConstructionToken c;
		Vertex v{ c };
		insert_vertex(i, v);
	}
}

void Graph::insert_vertexes(int n, int m)
{
	if (n < 0 || m < 0 || n > m)
	{
		std::cout << "error:参数不合法" << std::endl;
		return;
	}
	for (int i = n; i <= m; i++)
	{
		Vertex::ConstructionToken c;
		Vertex v{ c };
		insert_vertex(i, v);
	}
}

int Graph::get_vertex_number()
{
	return vertexes.size();
}

void Graph::insert_vertex(int id, Vertex v)
{
	std::pair<int, Vertex> temp(id, v);
	vertexes.insert(temp);
}

void Graph::insert_edge(int node, int new_edge)
{
	if (node == new_edge)
		return;
	//检查节点是否存在
	auto it = vertexes.find(node);
	if (it == vertexes.end())
	{
		//节点不存在的话，插入新节点
		this->insert_vertex(node);
		auto it1 = vertexes.find(node);
		//检查目的节点是否存在，否则插入新节点
		this->insert_vertex(new_edge);
		it1->second.insert_edge(new_edge);
		return;
	}
	it->second.insert_edge(new_edge);
}

void Graph::insert_edge(int node, int new_edge, float weight)
{
	if (node == new_edge)
		return;
	auto it = vertexes.find(node);
	if (it == vertexes.end())
		return;
	it->second.insert_edge(new_edge,weight);
}

void Graph::remove_edge(int node, int edge)
{
	auto it = vertexes.find(node);
	if (it == vertexes.end())
		return;
	it->second.remove_edge(edge);
}

//重载输出流，用于打印输出图
std::ostream& operator<<(std::ostream& out, const Graph& g)
{
	std::vector<int> end_points;
	for (auto& pair : g.vertexes)
	{
		end_points = pair.second.copy_edges();
		out << pair.first << " : ";
		for (auto& edge : end_points)
		{
			out << " -> " << edge;
		}
		out << std::endl;
	}
	return out;
}

void Graph::print_graph() const
{
	std::vector<int> end_points;
	for (auto& pair : vertexes)
	{
		end_points = pair.second.copy_edges();
		std::cout << pair.first << " : ";
		for (auto& edge : end_points)
		{
			std::cout << " -> " << edge;
		}
		std::cout << std::endl;
	}
}

//从邻接表文件创建图，邻接表文件中可以以'#'添加注释行
void Graph::read_adjacency_list(std::string file)
{
	std::ifstream ifs(file);
	std::string str;
	while (std::getline(ifs, str))
	{
		if (str.at(0) == '#')
		{
			continue;
		}
		std::vector<std::string> elems = Helper::split(str,' ');
		const int size = elems.size();
		if (size > 0)
		{
			int from = std::stoi(elems[0]);
			for (int i = 1; i < size; i++)
			{
				int to = std::stoi(elems[i]);
				this->insert_edge(from, to);
			}
		}
	}
}

float Graph::get_weight(int from, int to)
{
	if (from == to)
		return 0.0f;
	auto it = vertexes.find(from);
	if (it == vertexes.end())
		return -1;
	return it->second.get_weight(to);
}

void print_graph(const Graph& G)
{
	G.print_graph();
}