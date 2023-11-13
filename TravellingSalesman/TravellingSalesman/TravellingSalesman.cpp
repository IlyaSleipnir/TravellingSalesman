#include <iostream>
#include <sstream>
#include <fstream>
#include "Graph.h"

int main(int argc, char* argv[])
{
    std::vector<int> d[3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            d[i].push_back(j + i);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << d[i][j] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;


    Graph graph("file1.txt");

    std::vector<std::vector<int>> data = graph.dijkstra(0);

    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
        {
            std::cout << data[i][j] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;

    std::string line = "1 2 3 -5 10 123";

    std::stringstream ss(line);
    int num;
    while (ss >> num)
    {
        std::cout << num + 10 << std::endl;
    }

    //for (int i = 0; i < argc; i++) 
    //{
    //    std::string a = argv[i];
    //    std::cout << a << std::endl;
    //}
    
}