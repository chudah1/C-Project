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

class Airport {
public:
    static unordered_map<string, vector<string>> readAirports() {
        unordered_map <string, vector<string>> airportLocation;
        const string REGEX = ",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)";
        string readLine;
        ifstream ReadFile(
                R"(C:\Users\ohene\OneDrive\Documents\School Work\Assignments\Intermediate Computer Programming\C++\C-Project\airports.csv)");
        while (getline(ReadFile, readLine)) {
            vector <string> data;
            stringstream iss(readLine);
            while (iss.good()) {
                string splitLine;
                getline(iss, splitLine, ',');
                data.push_back(splitLine);
            }
            if (data[4] == "\\N") continue;
            string airportCode = data[4];
            string cityCountry = data[2] + ',' + ' ' + data[3];
            if (airportLocation.count(cityCountry) > 0) {
                airportLocation.at(cityCountry).push_back(airportCode);
            } else {
                vector <string> airport_codes;
                airport_codes.push_back(airportCode);
                airportLocation.insert({cityCountry, airport_codes});
            }
        }
        ReadFile.close();
        return airportLocation;

    }

};


