#pragma once
#include <string>
#include <vector>
#include <queue>

class Graph
{
public:
	Graph();
	Graph(std::string const& path);
	Graph(std::vector<std::vector<int>> data);
	std::vector<int> np_complete();
	std::vector<int> np_partial();
	~Graph();


	std::vector<std::vector<int>> dijkstra(int vertix);

private:
	std::vector<std::vector<int>> _data;
	int _size;

	//std::vector<int>* dijkstra(int vertix);
	std::vector<int> read_line(std::ifstream& file);
};
