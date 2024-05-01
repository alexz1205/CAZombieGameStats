#include "parse.h"
#include <cassert>
#include <algorithm>

using namespace std;

int main(){
    vector<vector<string>> data = splitData("Zombies.csv", ',');
    assert(data.size() != 0);

    map<string, vector<string>> dataByName;
    try {
        dataByName = mapByIdentifier(data, "Full Name");
    }catch (std::runtime_error& e){
        cout << e.what() << endl;
        exit(1);
    }

    printf("Total (Distinct) Participants: %d \n", data.size());

    map<string, vector<vector<string>>> dataByGrade;
    try {
        dataByGrade = consolidateByColumn(data, 3);
    }catch (std::runtime_error& e){
        cout << e.what() << endl;
        exit(1);
    }

    for (auto it = dataByGrade.begin(); it != dataByGrade.end(); ++ it){
        cout << it->first << ": " << it->second[0].size() << endl;
    }

    double sameGrade = 0, tot = 0;

    for (auto it = dataByName.begin(); it != dataByName.end(); ++ it){
        string anc = it->second[3];
        if (it->second[2] != "Teacher/Faculty/Community Dog"){
            if (dataByName.find(anc) != dataByName.end()){
                sameGrade += dataByName[anc][2] == it->second[2];
            }
            tot ++;
        }
    }

    printf("Same grade ratio: %llf\n", sameGrade/tot);

    map<string, int> bestZombie;

    for (auto it = dataByName.begin(); it != dataByName.end(); ++ it){
        string anc = it->second[3];
        bestZombie[anc] ++;
    }

    vector<pair<string, int>> all;
    vector<pair<string, int>> bests = {{"", -1}};
    for (auto it = bestZombie.begin(); it != bestZombie.end(); ++ it){
        if (it->second > bests[0].second){
            bests.clear();
            bests.push_back({it->first, it->second});
        }else if (it->second == bests[0].second){
            bests.push_back({it->first, it->second});
        }
        all.push_back({it->first, it->second});
    }
    cout << "Best Zombie: ";
    for (pair<string, int> p : bests){
        cout << p.first << " " << p.second << endl;
    }

    sort(all.begin(), all.end(), [](pair<string, int> a, pair<string, int> b){return (a.second == b.second ? a.first < b.first : a.second > b.second);});
    cout << "Best Zombies: " << endl;
    for (int x = 0; x < 10; x ++){
        cout << all[x].first << " " << all[x].second << endl;
    }
}