

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
        destinationAirportCode = destAirportCode;
        airlineCode = airline;
        stops = nStops;
    }

    string getDestinationAirportCode() {
        return destinationAirportCode;
    }

    string getAirlineCode() {
        return airlineCode;
    }

    int getStops() {
        return stops;
    }


    static unordered_map<string, vector<Route>> readRoutes() {
        unordered_map <string, vector<Route>> routeMap;
        string readLine;
        ifstream ReadFile("C:\\Users\\USER\\CLionProjects\\ROUTE PROJECT\routes.csv");
        while (getline(ReadFile, readLine)) {
            string data[8];
            int i = 0;
            string s;
            istringstream iss(readLine);
            while (getline(iss, s, ',')) {
                data[i] = s.c_str();
                ++i;
            }
            string sourceAirportCode = data[2];
            cout<<sourceAirportCode;
            string destinationAirportCode = data[4];
            string airlineId = data[0];
            int noOfStops = stoi(data[7]);
            Route routeDetail(destinationAirportCode, airlineId, noOfStops);
            if (routeMap.count(sourceAirportCode) != 1) {
                routeMap[sourceAirportCode] = vector<Route>();
            }
            routeMap[sourceAirportCode].push_back(routeDetail);

        }
        ReadFile.close();
        return routeMap;
    }
};

int main() {
    unordered_map<string, vector<Route>> route = Route::readRoutes();
    for(auto &it:route ){
        cout<<it.first <<endl;
    }
    return 0;
}


