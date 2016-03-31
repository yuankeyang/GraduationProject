#include <iostream>
#include <fstream>
#include <iomanip>
#include <Graph.h>
#include <Algorithm.h>
#include <ExeTime.h>

int main(int argc, char* argv[])
{
	std::string data_file = "facebook_combined.txt";
	std::string sketch_file = "facebook_sketch.txt";
	//std::string data_file = "test1.adjlist";
	//std::string sketch_file = "test1_sketch.txt";
	std::cout << "毕业设计:社交网络中基于隐私保护的好友推荐算法\n";
	std::cout << "************计算SKETCH********************\n";

	Graph g1(false);
	g1.read_adjacency_list_rel(data_file);
	
	Algorithm al(g1);
	std::ofstream ofs;
	ofs.open(sketch_file);
	ExeTime exeTm;
	if (ofs.is_open())
	{
		ofs.clear();
		for (Graph::ITR it = g1.begin(); it != g1.end(); it++) {
			VERTEXTYPE node = (*it).first;
			std::cout << "\rVertex:" << node;
			SAMPLE sample = al.offline_sample(node);
			ofs << node << " ";
			ofs << al.sample_to_string(sample);
		}
		std::cout << std::left << std::setw(20) << "\r---------------------------------------\n";
		ofs.close();
	}
	else 
	{
		std::cout << "文件" << sketch_file << "打开错误" << std::endl;
		ofs.close();
		return 0;
	}
	std::cout << "运行时间：" << exeTm.GetTmStr() << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}