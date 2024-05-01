#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <map>

std::vector<std::vector<std::string>> splitData(std::string file, char delim);

std::map<std::string, std::vector<std::string>> mapByIdentifier(std::vector<std::vector<std::string>> data, std::string identifier);

std::map<std::string, std::vector<std::string>> mapByColumn(std::vector<std::vector<std::string>> data, int id);

std::map<std::string, std::vector<std::vector<std::string>>> consolidateByIdentifier(std::vector<std::vector<std::string>> data, std::string identifier);

std::map<std::string, std::vector<std::vector<std::string>>> consolidateByColumn(std::vector<std::vector<std::string>> data, int id);
