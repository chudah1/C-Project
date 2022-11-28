#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <deque>
#include <fstream>
#include <sstream>
#include <unordered_set>


class Main {
public:
    std::vector<std::string> airportsInDest;
    std::vector<std::string> airportsInStart;
    std::string destinationAirport;
    std::unordered_map<std::string, std::vector<Route>> route;
    std::unordered_map<std::string, std::vector<std::string>> Airports;

    Main(std::string destinationAirport) {
        this->destinationAirport = destinationAirport;
        Airports = Airport::readAirports();
        route = Route::readRoutes();
    }


public:


    std::vector<Route> getSuccessorStates(std::string state) {
        return route.at(state);
    }

    bool foundDestination(std::string state) {
        if (Airports.count(destinationAirport) == 0) {
            cout << "Specified destination does not exist" << endl;
            exit(-1);
        }
        airportsInDest = Airports.at(destinationAirport);
        return std::find(airportsInDest.begin(), airportsInDest.end(), state) != airportsInDest.end();
    }

    bool contains(FlightNode node, deque <FlightNode> frontier) {
        for (auto &i: frontier) {
            if (node == i) {
                return true;
            }
        }
        return false;
    }


    void bfs(std::string startCountryCity) {
        std::vector<std::string> availableAirports = Airports.at(startCountryCity);

        std::deque<FlightNode> frontier;
        std::unordered_set<std::string> visited;
        for (auto &state: availableAirports) {
            FlightNode startNode = *new FlightNode(state);

            if (foundDestination(startNode.getState())) {
                startNode.solutionPath();
            }
            frontier.push_back(startNode);
        }

        while (!frontier.empty()) {
            FlightNode currentAirport = frontier.front();
            frontier.pop_front();
            visited.insert(currentAirport.getState());
            if (route.count(currentAirport.getState()) == 0) continue;
            std::vector<Route> succStates = getSuccessorStates(currentAirport.getState());
            for (auto &succState: succStates) {
                std::string destinationAirportCode = succState.getDestinationAirportCode();
                std::string airlineCode = succState.getAirlineCode();
                int nstops = succState.getStops();
                //
                FlightNode childNode = *new FlightNode(airlineCode, destinationAirportCode,
                                                       nstops + currentAirport.getNoOfStops(), &currentAirport);
                if (visited.count(childNode.getState()) == 0 && !contains(childNode, frontier)) {
                    if (foundDestination(childNode.getState())) {
                        childNode.solutionPath();
                    }
                    frontier.push_back(childNode);
                }
            }
        }

    }
};