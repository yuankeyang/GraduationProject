#include <iostream>
#include <boost/unordered_map.hpp>
#include <Graph.h>
#include <fstream>
#include <iomanip>
#include <Algorithm.h>
#include <Helper.h>

int main(int argc, char* argv[])
{
	Algorithm al;
	std::string sketch_file = "../test1_sketch.txt";
	al.read_sketchs(sketch_file);
	std::cout << "�����Ƽ�:\n";
	std::cout << "�����ʽ:>>id number" << std::endl;
	std::cout << "id Ϊ -1 ʱ�˳�����" << std::endl;
	std::cout << "-------------------" << std::endl;
	int node = 0;
	int number = 0;
	while (true)
	{
		std::cin.clear();
		std::cin >> node;
		if (node == -1)
			break;
		std::cin >> number;
		auto candiates = al.get_recommend(node);
		int i = 0;
		for (auto itr = candiates.begin();
		i < number; itr++, i++)
		{
			std::cout << "Vertex" << itr->first << ":"
				<< itr->second << std::endl;
		}
	}
	return EXIT_SUCCESS;
}