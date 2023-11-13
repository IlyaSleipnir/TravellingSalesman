#include <algorithm>
#include <fstream>
#include <sstream>
#include "Graph.h"

Graph::Graph()
{

}

std::vector<int>Graph::read_line(std::ifstream& file)
{
	std::string line;
	std::vector<int> res;

	std::getline(file, line);

	std::stringstream ss(line);
	int num;

	while (ss >> num)
	{
		res.push_back(num);
	}

	return res;
}

Graph::Graph(std::string const& path)
{
	std::ifstream file(path);
	std::vector<int> num_line;

	if (!file.is_open())
		throw "File opennig error!";

	while (!file.eof())
	{
		_data.push_back(read_line(file));
	}

	int size = _data.size();

	for (auto row : _data)
	{
		if (row.size() != size)
			throw "Matrix is not quare!";
	}

	_size = size;

	file.close();

}

Graph::Graph(std::vector<std::vector<int>> data)
{
	_size = data.size();
	for(auto row : data)
		if (row.size() != _size)
			throw "Matrix is not quare!";
	_data = data;
}

std::vector<int> Graph::np_complete()
{
	std::vector<int> min_path;
	int min_path_length = INT_MAX;
	std::vector<int> path;
	int path_length;

	std::vector<int> vertices;
	for (int i = 0; i < _size; i++)
	{
		vertices.push_back(i);
	}

	min_path = vertices;

	// Перебор всех перестановок вершин пути
	do
	{
		int elem;
		path_length = 0;

		for (int i = 1; i < _size; i++)
		{
			path.push_back(vertices[i]);
			elem = _data[vertices[i - 1]][vertices[i]];

			if (elem <= 0)
			{
				path_length = INT_MAX;
				break;
			}
			else
			{
				path_length += elem;
			}
		}

		// Замыкание пути
		elem = _data[vertices[_size - 1]][vertices[0]];
		if (elem <= 0)
			continue;

		if (path_length < min_path_length)
		{
			min_path = path;
			min_path_length = path_length;
		}

	} while (std::next_permutation(vertices.begin(), vertices.end()));

	return min_path;
}

std::vector<std::vector<int>> Graph::dijkstra(int start_vertix)
{
	std::vector<std::vector<int>> data;
	for (int i = 0; i < _size; i++)
	{
		std::vector<int> tmp;
		data.push_back(tmp);
	}

	//int min_path_length = INT_MAX;
	//std::vector<int> min_path;

	//int path_length;
	//std::vector<int> path;

	// Минимальное расстояние до вершины
	std::vector<int> disatnces;
	for (int i = 0; i < _size; i++)
	{
		disatnces.push_back(0);
	}
	
	// Список посещенных вершин
	std::vector<bool> visited;
	for (int i = 0; i < _size; i++)
	{
		visited.push_back(false);
	}

	for (int i = 0; i < _size; i++)
	{
		if (i == start_vertix)
		{
			std::vector<int> path;
			path.push_back(start_vertix);
			disatnces[i] = 0;
			data[i] = path;
		}
		else
		{
			disatnces[i] = INT_MAX;
		}
	}

	int ind = -1;
	// Минимальная дистанция до вершины
	int min;
	do
	{
		min = INT_MAX;
		for (int i = 0; i < _size; i++)
		{
			if (!visited[i] && disatnces[i] < INT_MAX)
			{
				min = disatnces[i];
				ind = i;
			}
		}

		if (min < INT_MAX)
		{
			for (int i = 0; i < _size; i++)
			{
				int elem = _data[ind][i];
				if (elem > 0)
				{
					int tmp = min + elem;
					if (tmp < disatnces[i])
					{
						disatnces[i] = tmp;
						data[i] = data[ind];
						data[i].push_back(i);
						/*path[i] = path[ind];
						path[i] =*/ 
					}
				}
			}
			visited[ind] = true;
		}
	} while (min < INT_MAX);

	return data;

}

std::vector<int> Graph::np_partial()
{


	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	std::vector<int> res;

	return res;
}

Graph::~Graph()
{
}