using namespace std;

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>


class Route {
private:
    string destinationAirportCode;
    string airlineCode;
    int stops;
public:
    Route(string destAirportCode, string airline, int nStops) {
        this->destinationAirportCode = destAirportCode;
        this->airlineCode = airline;
        this->stops = nStops;
    }

    string getDestinationAirportCode() {
        return this->destinationAirportCode;
    }

    string getAirlineCode() {
        return this->airlineCode;
    }

    int getStops() {
        return this->stops;
    }


    static unordered_map<string, vector<Route>> readRoutes() {
        /* Creating a map of string and vector of Route. */
        unordered_map <string, vector<Route>> routeMap;
        string readLine;
        ifstream ReadFile(
                R"(C:\Users\ohene\OneDrive\Documents\School Work\Assignments\Intermediate Computer Programming\C++\C-Project\routes.csv)");
        /* Reading the file line by line. */
        while (getline(ReadFile, readLine)) {
            vector <string> data;
            stringstream iss(readLine);
            while (iss.good()) {
                string splitLine;
                getline(iss, splitLine, ',');
                data.push_back(splitLine);
            }
            string sourceAirportCode = data[2];
            string destinationAirportCode = data[4];
            string airlineId = data[0];
            int noOfStops = stoi(data[7]);
            Route routeDetail(destinationAirportCode, airlineId, noOfStops);
            /* Checking if the key is already present in the map. If not, it is creating a new key with an empty vector. */
            if (routeMap.count(sourceAirportCode) > 0) {
                routeMap.at(sourceAirportCode).push_back(routeDetail);
            }

            /* Adding the routeDetail object to the vector of routes. */
            else {
                vector<Route> routeDetails;
                routeDetails.push_back(routeDetail);
                routeMap.insert({sourceAirportCode, routeDetails});
            }

        }
        ReadFile.close();
        return routeMap;
    }
};




