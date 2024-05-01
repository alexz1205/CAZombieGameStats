#include "parse.h"

std::vector<std::vector<std::string>> splitData(std::string file, char delim){
    std::vector<std::vector<std::string>> data;
    std::ifstream fIn;
    fIn.open(file);

    std::string unParse;
    
    while (std::getline(fIn, unParse)){
        std::vector<std::string> line;
        line.push_back("");
        for (char c: unParse){
            if (c == delim) {
                while (line.back().back() == ' '){
                    line.back().pop_back();
                }
                line.push_back("");
            }else line.back().push_back(c);
        }
        data.push_back(line);
    }

    fIn.close();

    return data;
}

std::map<std::string, std::vector<std::string>> mapByIdentifier(std::vector<std::vector<std::string>> data, std::string identifier){
    int id;
    for (; id < data[0].size() && identifier != data[0][id]; id ++);

    if (id == data[0].size()){
        throw std::runtime_error("No such identifier");
    }

    // std::cout << id << std::endl;

    std::map<std::string, std::vector<std::string>> mapping;

    for (std::vector<std::string> line : data){
        
        if (mapping.find(line[id]) != mapping.end()){
            // std::cout << line[id] << std::endl;
            throw std::runtime_error("Please use consolidateByIdentifer");
        }
        mapping.insert({line[id], {}});
        for (int x = 0; x < line.size(); x ++){
            if (x == id) continue;
            mapping[line[id]].push_back({line[x]});
        }
    }
    return mapping;
}

std::map<std::string, std::vector<std::string>> mapByColumn(std::vector<std::vector<std::string>> data, int id){

    // std::cout << id << std::endl;

    std::map<std::string, std::vector<std::string>> mapping;

    for (std::vector<std::string> line : data){
        std::vector<std::string> copy (line);

        copy.erase(copy.begin()+id);
        
        if (mapping.find(line[id]) != mapping.end()){
            // std::cout << line[id] << std::endl;
            throw std::runtime_error("Please use consolidateByIdentifer");
        }
        mapping.insert({line[id], copy});
    }
    return mapping;
}

std::map<std::string, std::vector<std::vector<std::string>>> consolidateByColumn(std::vector<std::vector<std::string>> data, int id){

    std::map<std::string, std::vector<std::vector<std::string>>> mapping;

    for (std::vector<std::string> line : data){

        if (mapping.find(line[id]) != mapping.end()){
            for (int x = 0; x < line.size(); x ++){
                if (x == id) continue;
                mapping[line[id]][x - (x > id)].push_back(line[x]);
            }
        }else {
            mapping.insert({line[id], {}});
            for (int x = 0; x < line.size(); x ++){
                if (x == id) continue;
                mapping[line[id]].push_back({line[x]});
            }
        }
    }
    return mapping;
}

// int main(){

// }