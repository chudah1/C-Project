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
        ifstream ReadFile("airports.csv");
        while (getline(ReadFile, readLine)){
            string data[14];
            int i = 0;
            string s;
            istringstream iss(readLine);
            while (getline(iss,s,',')) {
                data[i] =s.c_str();
                ++i;
            }
            if (data[4] == "\\N") continue;
            string airportCode = data[4];
            cout<<airportCode;
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
