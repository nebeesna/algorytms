#include "pch.h"
#include<iostream>
#include<vector>
using namespace  std;

const int _INFINITY = 10000;

class Graph
{
private:
	int number_of_vertexes;
	vector<vector<int>> adjacency_matrix; // матриц€ сум≥жност≥
public:

	Graph()
	{
		number_of_vertexes = 0;
	}
	Graph(int num, vector<vector<int>> matrx)
	{
		number_of_vertexes = num;
		adjacency_matrix = matrx;
	}
	~Graph() {};
	bool is_connected()
	{
		bool res = true;
		for (int i = 0; i < number_of_vertexes; i++)
		{
			for (int j = 0; j < number_of_vertexes; j++)
			{
				if (i == j && adjacency_matrix[i][j] != 0)
				{
					res &= false;
				}
			}
		}
		return res;
	}
	pair<int, vector<int>> algorithm_dijkstra(int start, int finish)
	{
		if (is_connected()) {
			vector<vector<int>> weight(number_of_vertexes, vector<int>(number_of_vertexes));
			vector<int> distance(number_of_vertexes);
			vector<int> way(number_of_vertexes);
			vector<int> visited(number_of_vertexes);
			int  min_distance = _INFINITY, nextnode, count = 0, temp = 0;
			for (int i = 0; i < number_of_vertexes; i++)
			{
				for (int j = 0; j < number_of_vertexes; j++)
				{
					if (adjacency_matrix[i][j] == 0)
					{
						weight[i][j] = _INFINITY;
					}
					else weight[i][j] = adjacency_matrix[i][j];
				}
			}

			for (int i = 0; i < number_of_vertexes; i++)
			{
				distance[i] = weight[start][i];
				way[i] = start;
				visited[i] = 0;
			}

			distance[start] = 0;
			visited[start] = 1;
			count = 1;
			while (count < number_of_vertexes - 1)
			{
				for (int i = 0; i < number_of_vertexes; i++)
				{
					if (distance[i] < min_distance && !visited[i])
					{
						min_distance = distance[i];
						nextnode = i;
					}
				}
				visited[nextnode] = 1;
				for (int i = 0; i < number_of_vertexes; i++)
				{
					if (!visited[i])
					{
						if (min_distance + weight[nextnode][i] < distance[i])
						{
							distance[i] = min_distance + weight[nextnode][i];
							way[i] = nextnode;
						}
					}
				}
				count++;
			}
			vector<int> way_res;
			temp = finish;
			way_res.push_back(finish);
			do {
				temp = way[temp];
				way_res.push_back(temp);
			} while (temp != start);
			pair<int, vector<int>> res;
			res = make_pair(distance[finish], way_res);
			return res;
		}
		else throw exception("graph is not connected.");
	}
};
TEST(GraphTest, ConnectedTest1) {
	vector <vector <int> > b(3, vector <int>(3));
	b = {
		  {0 ,1 ,0 },
		  {1 ,0 ,5 },
		  {0 ,5 ,0 }, };
	Graph g(3, b);
	EXPECT_TRUE(g.is_connected());
}
TEST(GraphTest, ConnectedTest2) {
	vector <vector <int> > b(4, vector <int>(4));
	b = {
		  {0 ,1 ,0, 3 },
		  {1 ,3 ,5, 5 },
		  {0 ,5 ,0, 8 }, 
		  {6 ,2 ,0, 8 }, };
	Graph g(4, b);
	EXPECT_FALSE(g.is_connected());
}
TEST(GraphTest, algorithm_dijkstraTest1) {
	vector <vector <int> > b(5, vector <int>(5));
	b = {
					  {0 ,1 ,0 ,3 ,10},
					  {1 ,0 ,5 ,0 ,0},
					  {0 ,5 ,0, 2 ,1},
					  {3 ,0 ,2 ,0 ,6},
					  {10,0 ,1 ,6 ,0} };
	Graph g(5, b);
	EXPECT_EQ( 10 ,g.algorithm_dijkstra(0, 4).first);
}
TEST(GraphTest, algorithm_dijkstraTest2) {
	vector <vector <int> > b(5, vector <int>(5));
	b = {
					  {0 ,1 ,0 ,3 ,10},
					  {3 ,0 ,5 ,0 ,0},
					  {0 ,6 ,0, 8 ,1},
					  {3 ,0 ,3 ,0 ,6},
					  {9,0 ,1 ,6 ,0} };
	Graph g(5, b);
	EXPECT_EQ( 6,g.algorithm_dijkstra(1, 3).first);
}
TEST(GraphTest, algorithm_dijkstraTest3) {
	vector <vector <int> > b(5, vector <int>(5));
	b = {
					  {0 ,1 ,0 ,3 ,10},
					  {3 ,7 ,5 ,0 ,0},
					  {0 ,6 ,4, 8 ,1},
					  {3 ,0 ,3 ,0 ,6},
					  {9,0 ,1 ,6 ,0} };
	Graph g(5, b);
	try
	{
		g.algorithm_dijkstra(2, 4);
	}
	catch (const std::exception& ex)
	{
		cout << endl <<ex.what() << endl;
	}
}

TEST(GraphTest, algorithm_dijkstraTest4) {
	vector <vector <int> > b(4, vector <int>(4));
	b = {
					  {0 ,1 ,3, 2 },
					  {0 ,0 ,1, 1 },
					  {0 ,0 ,0 , 1},
					  {2 ,3 ,0 , 0} };
	Graph g(4, b);
	vector<int> res(0);
	res.push_back(2);
	res.push_back(1);
	res.push_back(0);

	EXPECT_EQ(res, g.algorithm_dijkstra(0, 2).second);
	EXPECT_EQ(2, g.algorithm_dijkstra(0, 2).first);
}