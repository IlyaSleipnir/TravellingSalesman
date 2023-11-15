#include <iostream>
#include <sstream>
#include <fstream>
#include "Graph.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");

    std::string key;
    std::string path;
    std::string help_str = "Программа считывает из файла матрицу путей и решает заду коммивояжера.\n\n";
    help_str += "Параметры:\n\n";
    help_str += "\t-f -- путь к файлу с матрицей\n";
    help_str += "\t-m -- режим работы программы:\n";
    help_str += "\t\tnp_complete -- оптималное решение полным перебором\n";
    help_str += "\t\tnp_partial -- приближенное решение простым жадным алгоритмом\n";
    help_str += "\t-h -- вывод описания программы\n\n";
    help_str += "Формат файла:\n\n";
    help_str += "\t0 a01 a02 ... a0n\n";
    help_str += "\ta10 0 a12 ... a1n\n";
    help_str += "\t.................\n";
    help_str += "\tan0 an1 an2 ... 0\n\n";
    help_str += "\tГде aXY -- целочисленное расстояние от точки X до точки Y, отсутствие пути обозначается числом 0.\n";
    help_str += "\tМатрица считается связной.\n";

    bool complite_mode;

    for (int i = 1; i < argc; i++)
    {
        if (std::string(argv[i]) == "-m")
        {
            std::string mode_str = argv[++i];
            if (mode_str == "np_partial")
                complite_mode = false;
            if (mode_str == "np_complete")
                complite_mode = true;
        }

        if (std::string(argv[i]) == "-f")
            path = argv[++i];

        if (std::string(argv[i]) == "-h")
            std::cout << help_str << std::endl;
    }
    
    if (path != "")
    {
        try
        {
            std::vector<int> res;
            int len = 0;
            Graph graph(path);
            if (complite_mode)
                res = graph.np_complete();
            else
                res = graph.np_partial();

            std::cout << "Путь: ";
            for (auto elem : res)
                std::cout << elem << " ";
            std::cout << std::endl;
            for (int i = 1; i < res.size(); i++)
                len += graph.get_elem(res[i - 1], res[i]);
            std::cout << "Длина пути: " << len << std::endl;
        }
        catch (std::string error)
        {
            std::cout << error << std::endl;
        }
    }
}