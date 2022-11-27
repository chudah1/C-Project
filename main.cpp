#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include "Route.cpp"
#include <queue>
#include "FlightNode.cpp"
#include <unordered_set>
#include "Airport.cpp"


class Main{
    inline static std::unordered_map<std::string, std::vector<Route>> route =Route::readRoutes();
    inline static std::unordered_map<std::string, std::vector<std::string>> Airports = Airport::readAirports();


private:
    static std::vector<std::string> airportsInDest ;
    static std::vector<std::string> airportsInStart;
    static std::string startAirport;
    static std::string destinationAirport;


/* A static method that returns a vector of routes. */
public:
    static std::vector<Route> getSuccessorStates(std::string state){
        return route.at(state);
    }
    static bool foundDestination(std::string state){
        if (Airports.count(destinationAirport)==0){
            cout<<"Specified destination does not exist" <<endl;
            exit(-1);
        }
        airportsInDest = Airports.at(destinationAirport);
        return std::find(airportsInDest.begin(), airportsInDest.end(), state)!=airportsInDest.end();
    }



    static void bfs(std::string startCountryCity){
        std::vector<std::string> availableAirports = Airports.at(startCountryCity);
        std::queue<FlightNode> frontier;
        std::unordered_set<std::string> visited;
        for (auto &state: availableAirports){
            FlightNode startNode = *new FlightNode(state);
            if (foundDestination(startNode.getState())) {
                startNode.solutionPath();
            }
            frontier.push(startNode);

        }

        while (frontier.size()>0){
            FlightNode currentAirport = frontier.front();
            frontier.pop();
            visited.insert(currentAirport.getState());
            if (route.count(currentAirport.getState())==0) continue;
            std::vector<Route> succStates = getSuccessorStates(currentAirport.getState());
            for (auto &succState:succStates){
                std::string destinationAirportCode = succState.getDestinationAirportCode();
                std::string airlineCode = succState.getAirlineCode();
                int nstops = succState.getStops();
                //
                FlightNode childNode= *new FlightNode(airlineCode, destinationAirportCode, nstops+currentAirport.getNoOfStops(), &currentAirport);
                if (visited.count(childNode.getState())==0 && frontier.empty()){ //error
                    if (foundDestination(childNode.getState())) {
                        childNode.solutionPath();
                    }
                    frontier.push(childNode);
                }
            }
        }

    }
};

//int main(){
//    const std::string REGEX= "\\s*,\\s*";
//    const std::string REPLACE = ",";
//    std::ifstream inputFile("london-banjul.txt");
//
//
//    return 0;
//
//}