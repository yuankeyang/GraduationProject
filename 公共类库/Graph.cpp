#include <iostream>
#include <string>
#include <utility>
#include <fstream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Helper.h"

#define random(x) (rand() % x)

Graph::Graph()
{
	edges = 0;
	directed = true;
}

Graph::Graph(bool is_directed)
{
	edges = 0;
	directed = is_directed;
}

void Graph::insert_vertex(VERTEXTYPE& id)
{
	Vertex::ConstructionToken c;
	Vertex v{ c };
	insert_vertex(id, v);
}

std::size_t Graph::get_vertex_number()
{
	return vertexes.size();
}

void Graph::insert_vertex(VERTEXTYPE& id, Vertex& v)
{
	std::pair<VERTEXTYPE, Vertex> temp(id, v);
	vertexes.insert(temp);
}

void Graph::insert_edge(VERTEXTYPE& node, VERTEXTYPE& new_edge)
{
	if (node == new_edge)
		return;
	//�ڵ㲻���ڵĻ��������½ڵ�
	this->insert_vertex(node);
	auto it1 = vertexes.find(node);
	//���Ŀ�Ľڵ��Ƿ���ڣ���������½ڵ�
	this->insert_vertex(new_edge);
	auto it2 = vertexes.find(new_edge);
	std::pair<boost::unordered_map<VERTEXTYPE, Edge>::iterator, bool> ret = it1->second.insert_edge(new_edge);
	//���������ͼ
	if (!directed) 
	{
		ret = it2->second.insert_edge(node);
	}
	if (ret.second)
	{
		edges += 1;
		it1->second.out_degree += 1;
		it2->second.in_degree += 1;
	}
	
}
/*�����*/
void Graph::insert_edge(VERTEXTYPE& node, VERTEXTYPE& new_edge, EDGE_DATE_TYPE& weight)
{
	if (node == new_edge)
		return;
	this->insert_vertex(node);
	this->insert_vertex(new_edge);
	auto it1 = vertexes.find(node);
	auto it2 = vertexes.find(new_edge);
	std::pair<boost::unordered_map<VERTEXTYPE, Edge>::iterator, bool> ret = it1->second.insert_edge(new_edge,weight);
	if (!directed)
	{
		ret = it2->second.insert_edge(node,weight);
	}
	if (ret.second) 
	{
		edges += 1;
		it1->second.out_degree += 1;
		it2->second.in_degree += 1;
	}
		
}
/*�Ƴ���*/
void Graph::remove_edge(VERTEXTYPE& node, VERTEXTYPE& edge)
{
	auto it1 = vertexes.find(node);
	auto it2 = vertexes.find(edge);
	if (it1 == vertexes.end())
		return;
	it1->second.remove_edge(edge);
	edges -= 1;
	assert(it1->second.out_degree > 0);
	it1->second.out_degree -= 1;
	assert(it2->second.in_degree > 0);
	it2->second.in_degree -= 1;
}

/*������������ڴ�ӡ���ͼ*/
std::ostream& operator<<(std::ostream& out, const Graph& g)
{
	std::vector<VERTEXTYPE> end_points;
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
/*��ӡͼ*/
void Graph::print_graph() const
{
	std::vector<VERTEXTYPE> end_points;
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

/*���ڽӱ��ļ�����ͼ���ڽӱ��ļ��п�����'#'���ע����*/
void Graph::read_adjacency_list_rel(std::string& file)
{
	std::cout << "���ڽӱ��ļ��ж�ȡͼ��\n";
	std::ifstream ifs(file);
	std::string str;
	srand((int)time(0));
	while (std::getline(ifs, str))
	{
		if (str.at(0) == '#')
		{
			continue;
		}
		std::vector<std::string> elems = Helper::split(str,' ');
		const int size = static_cast<int>(elems.size());
		if (size > 0)
		{
			VERTEXTYPE from = std::stoi(elems[0]);
			for (int i = 1; i < size; i++)
			{
				VERTEXTYPE to = std::stoi(elems[i]);
				EDGE_DATE_TYPE weight = random(100) + 1;
				this->insert_edge(from, to, weight);
				std::string str = "\rinsert edge(";
				str.append(std::to_string(from));
				str.append(", ");
				str.append(std::to_string(to));
				str.append("), weight(");
				str.append(std::to_string(weight));
				str.append(")");
				std::cout << std::left << std::setw(20) << str;
			}
		}
	}
	std::cout << std::left << std::setw(20) << "\r---------------------------------------";
	std::cout << std::endl << "��ȡ��ϣ�" << std::endl;
	std::cout << "�������" << get_vertex_number() << std::endl;
	std::cout << "������" << get_edges() << std::endl;
}
/*��ȡ�ߵ�Ȩ*/
EDGE_DATE_TYPE Graph::get_weight(VERTEXTYPE& from, VERTEXTYPE& to)
{
	if (from == to)
		return 0;
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
EDGE_DATE_TYPE Graph::bfs(VERTEXTYPE& from, VERTEXTYPE& to)
{
	/*HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = 0;
	coord.Y = 7;*/

	if (from == to)
		return 0;
	boost::unordered_map<VERTEXTYPE, VERTEXTYPE> flaged;
	std::queue<VERTEXTYPE> queue;
	std::pair<VERTEXTYPE, VERTEXTYPE> temp(from, from);
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
				VERTEXTYPE temp = it;
				EDGE_DATE_TYPE temp_weight = get_weight(temp, to);
				/*
				std::string str = "bfs(";
				std::string from_str = std::to_string(from);
				std::string to_str = std::to_string(to);
				std::string weight_str = std::to_string(temp_weight);
				str.append(from_str);
				str.append(", ");
				str.append(to_str);
				str.append("):");
				str.append(to_str);
				str.append("<-(");
				str.append(weight_str);
				str.append(")-");
				*/
				EDGE_DATE_TYPE weight = 0;
				weight += temp_weight;
				while (temp != from)
				{
					VERTEXTYPE next = flaged[temp];
					temp_weight = get_weight(next, temp);
					/*str.append(std::to_string(temp));
					str.append("<-(");
					str.append(std::to_string(temp_weight));
					str.append(")-");*/
					weight += temp_weight;
					temp = next;
				}
				/*str.append(from_str);
				SetConsoleCursorPosition(hConsole, coord);
				std::cout << std::left << std::setw(160) << str;*/
				std::string str = "\rbfs(";
				str.append(std::to_string(from));
				str.append(",");
				str.append(std::to_string(to));
				str.append("):");
				str.append(std::to_string(weight));
				std::cout << std::setw(20) << str;
				return weight;
			}

			if (flaged.find(item) != flaged.end())
				continue;
			else
			{
				std::pair<VERTEXTYPE, VERTEXTYPE> temp(item, it);
				flaged.insert(temp);
				queue.push(item);
			}
		}
	}
	return -1;
}

int Graph::get_edges()
{
	return edges;
}

Graph::ITR Graph::begin()
{
	return this->vertexes.begin();
}

Graph::ITR Graph::end()
{
	return this->vertexes.end();
}

int Graph::get_in_degree(VERTEXTYPE & v)
{
	auto it = vertexes.find(v);
	return it->second.in_degree;
}

int Graph::get_out_degree(VERTEXTYPE & v)
{
	auto it = vertexes.find(v);
	return it->second.out_degree;
}
