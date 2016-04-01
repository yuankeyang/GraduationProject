#include <iostream>
#include <boost/unordered_map.hpp>
#include <Graph.h>
#include <fstream>
#include <iomanip>
#include <Algorithm.h>
#include <Helper.h>
#include <ExeTime.h>

int main(int argc, char* argv[])
{
	Algorithm al;
	std::string sketch_file = "../facebook_sketch.txt";
	//std::string sketch_file = "../test1_sketch.txt";
	al.read_sketchs(sketch_file);
	std::cout << "好友推荐:\n";
	std::cout << "命令格式:>>id number" << std::endl;
	std::cout << "id 为负数时退出程序" << std::endl;
	std::cout << "-------------------" << std::endl;
	int node = 0;
	int number = 0;
	while (true)
	{
		std::cin.clear();
		std::cin >> node;
		if (node < 0)
			break;
		std::cin >> number;
		ExeTime exeTm;
		auto candiates = al.get_recommend(node);
		int i = 0;
		for (auto itr = candiates.begin();
		i < number && itr != candiates.end(); itr++, i++)
		{
			std::cout << "Vertex" << std::setw(4) << itr->first << ", closeness = "
				<< itr->second << std::endl;
		}
		std::cout << "运行时间：" << exeTm.GetTmStr() << std::endl;
		std::cout << "-------------------" << std::endl;
	}
	return EXIT_SUCCESS;
}