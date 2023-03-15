#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

struct Faculty
{
    std::string university;
    int year;
};
const int SIZE = 100;

std::map<std::string, Faculty> createMap(std::string filename);
void printMap(std::map<std::string, Faculty> csMap);

int main(int argc, char *argv[])
{
    std::map<std::string, Faculty> Map = createMap("lecture6_exercise_w23.csv");
    printMap(Map);

    return 0;
}

std::map<std::string, Faculty> createMap(std::string filename)
{
    std::ifstream inputFile(filename);
    Faculty faculty[SIZE];
    int count = 0;
    std::string line;
    std::map<std::string, Faculty> Map;

    while (!inputFile.eof())
    {
        std::string name;
        std::getline(inputFile, name, ',');
        std::getline(inputFile, faculty[count].university, ',');
        std::string year;
        std::getline(inputFile, year);
        faculty[count].year = std::stoi(year);
        // 最终 Map会按 Key排序
        Map[name] = faculty[count];
        count++;
    }
    return Map;
}

void printMap(std::map<std::string, Faculty> csMap)
{
    for (auto it = csMap.begin(); it != csMap.end(); it++)
    {
        // structured binding
        auto [name, faculty] = *it;
        std::cout << name << " " << faculty.university << " " << faculty.year << std::endl;
    }
}