//
// Created by USER on 11/17/2022.
//
using namespace std;
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

class Airport{
public:
    static unordered_map<string, vector<string>> readAirports(){
        unordered_map<string, vector<string>> airportLocation;
        const string REGEX= ",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)";
        string readLine;
        ifstream ReadFile("C:\\Users\\USER\\CLionProjects\\ROUTE PROJECT\\airports.csv");
        while (getline(ReadFile, readLine)){
            vector<string> data;
            stringstream iss(readLine);
            while (iss.good()) {
                string splitLine;
                getline(iss, splitLine, ',');
                data.push_back(splitLine);
            }
            if (data[4] == "\\N") continue;
            string airportCode = data[4];
            string cityCountry = data[2] + ',' + data[3];
            if(airportLocation.count(cityCountry)==0){
                airportLocation[cityCountry];
            }
            else{
                airportLocation[cityCountry].push_back(airportCode);
            }
        }
        ReadFile.close();
        return airportLocation;

    }

};
//int main() {
//    unordered_map<string, vector<string>> airport = Airport::readAirports();
//    cout<<airport.size();
//    for(auto &it:airport ){
//        cout<<it.first <<endl;
//    }
//    return 0;
//}

