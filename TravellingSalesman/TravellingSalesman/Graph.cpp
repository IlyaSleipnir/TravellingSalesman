#include <algorithm>
#include <fstream>
#include <sstream>
#include "Graph.h"

Graph::Graph()
{

}

const std::vector<std::vector<int>> Graph::get_data()
{
	return _data;
}

const int Graph::get_elem(int i, int j)
{
	return _data[i][j];
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
	std::vector<std::vector<int>> data;

	if (!file.is_open())
		throw std::string{ "File opennig error!" };

	while (!file.eof())
	{
		data.push_back(read_line(file));
	}

	int size = data.size();

	for (auto row : data)
	{
		if (row.size() != size)
			throw std::string{ "Matrix is not quare!" };
	}

	if (!is_solvable(data))
		throw std::string{ "Matrix is not solvable!" };

	_size = size;
	_data = data;

	file.close();

}

Graph::Graph(std::vector<std::vector<int>> data)
{
	if (!is_solvable(data))
		throw std::string{ "Matrix is not solvable!" };

	int size = data.size();
	for(auto row : data)
		if (row.size() != size)
			throw std::string{ "Matrix is not quare!" };

	_size = size;
	_data = data;
}

std::vector<int> Graph::np_complete()
{
	std::vector<int> min_path;
	int min_length = INT_MAX;

	std::vector<int> vertices;
	for (int i = 0; i < _size; i++)
	{
		vertices.push_back(i);
	}

	min_path = vertices;

	// Перебор всех перестановок вершин пути
	do
	{
		std::vector<int> path;
		path.push_back(vertices[0]);
		int length = 0;
		int elem;

		for (int i = 1; i < _size; i++)
		{
			path.push_back(vertices[i]);
			elem = _data[vertices[i - 1]][vertices[i]];

			if (elem <= 0)
			{
				length = INT_MAX;
				break;
			}
			else
			{
				length += elem;
			}
		}

		

		if (length < min_length)
		{
			// Замыкание пути
			elem = _data[vertices[_size - 1]][vertices[0]];
			if (elem <= 0)
				continue;
			path.push_back(vertices[0]);
			length += elem;

			min_path = path;
			min_length = length;
		}

	} while (std::next_permutation(vertices.begin(), vertices.end()));

	return min_path;
}

std::vector<int> Graph::np_partial()
{
	int min_length = INT_MAX;
	std::vector<int> min_path;
	
	for (int k = 0; k < _size; k++)
	{
		int length = 0;
		std::vector<int> path;
		path.push_back(k);
		// Флаг завершенности пути по-умолчанию true
		bool is_finished = true;
		
		while (path.size() != _size)
		{
			int min_d = INT_MAX;
			int last_vetix = path.back();
			int next_vertix;
			// Флаг продвижения на очередной итерации 
			bool is_moving = false;

			for (int i = 0; i < _data[last_vetix].size(); i++)
			{
				int d = _data[last_vetix][i];
				if (!vector_consists(path, i) && d < min_d && d > 0)
				{
					min_d = d;
					next_vertix = i;
					is_moving = true;
				}
			}

			if (!is_moving)
			{
				is_finished = false;
				break;
			}

			path.push_back(next_vertix);
			length += min_d;
		}

		// Замыкание пути
		int last_d = _data[path.back()][k];
		if (last_d > 0)
		{
			path.push_back(k);
			length += last_d;
		}
		else
			is_finished = false;

		if (!is_finished)
			continue;

		if (length < min_length)
		{
			min_length = length;
			min_path = path;
		}

	}

	if (min_path.size() == 0)
		throw std::string{ "Unable to solve by greedy algorithm" };

	return min_path;
}

bool Graph::vector_consists(std::vector<int> v, int elem)
{
	if (std::find(v.begin(), v.end(), elem) != v.end())
		return true;
	else
		return false;
}

bool Graph::is_solvable(std::vector<std::vector<int>> data)
{
	for (auto vec : data)
	{
		int count_paths = std::count_if(vec.begin(), vec.end(), [](int i) {return i > 0; });
		if (count_paths < 2)
			return false;
	}
	return true;
}

Graph::~Graph()
{
}