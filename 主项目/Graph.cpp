#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <fstream>
#include <queue>
#include <algorithm>
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Helper.h"

void Graph::insert_vertex(std::string id)
{
	Vertex::ConstructionToken c;
	Vertex v{ c };
	insert_vertex(id, v);
}

int Graph::get_vertex_number()
{
	return vertexes.size();
}

void Graph::insert_vertex(std::string id, Vertex v)
{
	std::pair<std::string, Vertex> temp(id, v);
	vertexes.insert(temp);
}

void Graph::insert_edge(std::string node, std::string new_edge)
{
	if (node == new_edge)
		return;
	//�ڵ㲻���ڵĻ��������½ڵ�
	this->insert_vertex(node);
	auto it1 = vertexes.find(node);
	//���Ŀ�Ľڵ��Ƿ���ڣ���������½ڵ�
	this->insert_vertex(new_edge);
	it1->second.insert_edge(new_edge);
}

void Graph::insert_edge(std::string node, std::string new_edge, float weight)
{
	if (node == new_edge)
		return;
	this->insert_vertex(node);
	this->insert_vertex(new_edge);
	auto it = vertexes.find(node);
	it->second.insert_edge(new_edge,weight);
}

void Graph::remove_edge(std::string node, std::string edge)
{
	auto it = vertexes.find(node);
	if (it == vertexes.end())
		return;
	it->second.remove_edge(edge);
}

//��������������ڴ�ӡ���ͼ
std::ostream& operator<<(std::ostream& out, const Graph& g)
{
	std::vector<std::string> end_points;
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
	std::vector<std::string> end_points;
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

//���ڽӱ��ļ�����ͼ���ڽӱ��ļ��п�����'#'���ע����
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
			std::string& from = elems[0];
			for (int i = 1; i < size; i++)
			{
				std::string& to = elems[i];
				this->insert_edge(from, to);
			}
		}
	}
}

float Graph::get_weight(std::string from, std::string to)
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

//BFS�㷨ʵ��
void Graph::bfs(std::string from, std::string to)
{
	if (from == to)
		return;
	std::map<std::string,std::string> flaged;
	std::queue<std::string> queue;
	std::pair<std::string, std::string> temp(from, "");
	flaged.insert(temp);
	queue.push(from);
	while (!queue.empty())
	{
		auto it = queue.front();
		queue.pop();
		auto current_vertex = vertexes.find(it);
		auto sub_vertexes = current_vertex->second.copy_edges();
		for (unsigned int i = 0; i < sub_vertexes.size(); i++)
		{
			auto item = sub_vertexes[i];
			if (item == to)
			{
				std::string temp = it;
				std::cout << to << "<-";
				while (temp != from)
				{
					std::cout << temp << "<-";
					temp = flaged[temp];
				}
				std::cout << from << std::endl;
				return;
			}

			if (flaged.find(item) != flaged.end())
				continue;
			else
			{
				std::pair<std::string, std::string> temp(item, it);
				flaged.insert(temp);
				queue.push(item);
			}
		}
	}
}