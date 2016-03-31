#include <gtest/gtest.h>
#include <Graph.h>
#include <string>
#include <Algorithm.h>

TEST(GraphTest, UndirectedGraphTest)
{
	Graph g(false);
	int v1 = 1;
	int v2 = 2;
	int v3 = 3;
	int v4 = 4;
	int v5 = 5;
	int v6 = 6;
	int v1v2 = 12;
	int v1v3 = 13;
	int v1v4 = 14;
	int v1v5 = 15;
	int v2v6 = 6;
	int v3v5 = 35;
	int v4v6 = 46;
	int v2v1 = 21;
	g.insert_edge(v1, v2, v1v2);
	g.insert_edge(v1, v3, v1v3);
	g.insert_edge(v1, v4, v1v4);
	g.insert_edge(v1, v5, v1v5);
	g.insert_edge(v2, v6, v2v6);
	g.insert_edge(v3, v5, v3v5);
	g.insert_edge(v4, v6, v4v6);
	
	//vertex: 6
	EXPECT_EQ(6, (int)g.get_vertex_number());
	//edges: 7
	EXPECT_EQ(7, g.get_edges());
	//degree
	EXPECT_EQ(4, g.get_in_degree(v1) + g.get_out_degree(v1));
	EXPECT_EQ(2, g.get_in_degree(v2) + g.get_out_degree(v2));
	//bfs
	EXPECT_NE(v1v2 + v2v6, g.bfs(v1, v6));
	//insert fail
	g.insert_edge(v2, v1, v2v1);
	EXPECT_NE(v2v1, g.get_weight(v2, v1));
	EXPECT_EQ(v1v2, g.get_weight(v2, v1));
	EXPECT_EQ(v1v2, g.get_weight(v1, v2));
	//same vertex
	EXPECT_EQ(0, g.get_weight(v1, v1));
	//remove one edge
	g.remove_edge(v1, v4);
	//vertex: 5
	EXPECT_EQ(6, (int)g.get_vertex_number());
	//edges: 6
	EXPECT_EQ(6, g.get_edges());
	EXPECT_EQ(-1, g.get_weight(v1, v4));
	EXPECT_EQ(3, g.get_in_degree(v1) + g.get_out_degree(v1));
	EXPECT_EQ(1, g.get_in_degree(v4) + g.get_out_degree(v4));
}

TEST(GraphTest, ReadAdjListTest)
{
	Graph g(false);
	std::string file = "../test.adjlist";
	g.read_adjacency_list_rel(file);
	EXPECT_EQ(100, (int)g.get_vertex_number());
	int v1 = 1;
	int v151 = 151;
	std::cout << "d(1, 151):" << g.get_weight(v1, v151) << std::endl;
}

TEST(AlgorithmTest, OffLineSampleTest)
{
	Graph g(false);
	std::string file = "../test.adjlist";
	g.read_adjacency_list_rel(file);
	Algorithm al(g);
	VERTEXTYPE node = (g.begin())->first;
	SAMPLE sample = al.offline_sample(node);
	EXPECT_LE(0, sample.size());
}

TEST(AlgorithmTest, EstimateDistanceTest)
{
	Algorithm al;
	std::string sketch_file = "../test1_sketch.txt";
	al.read_sketchs(sketch_file);
	int d = al.estimate_distance(1, 151);
	std::cout << "d(1, 151) = " << d << std::endl;
}

TEST(AlgorithmTest, CalculateClosenessTest)
{
	Algorithm al;
	std::string sketch_file = "../test1_sketch.txt";
	al.read_sketchs(sketch_file);
	double closeness = al.calculate_closeness(1, 151);
	std::cout << "S(1,151) = " << closeness << std::endl;
	EXPECT_EQ(0, al.calculate_closeness(151, 151));
}