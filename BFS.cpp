#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <deque>
#include <set>
#include <algorithm>
#include "Route.cpp"
#include <memory>
#include "Airport.cpp"
#include "FlightNode.cpp"

using std::shared_ptr;
using std::make_shared;

class Main {
public:
    std::vector<std::string> airportsInDest;
    std::vector<std::string> airportsInStart;
    std::string destinationAirport;
    std::unordered_map<std::string, std::vector<Route>> route;
    std::unordered_map<std::string, std::vector<std::string>> Airports;

    explicit Main(std::string destination) {
        this->destinationAirport = destination;
        Airports = Airport::readAirports();
        route = Route::readRoutes();
    }


public:


    /**
     * Given a state, return a vector of all possible successor states
     *
     * @param state The current state of the problem.
     *
     * @return A vector of routes.
     */
    std::vector<Route> getSuccessorStates(std::string state) {
        return route.at(state);
    }

    /**
     * This function checks if the destination airport is in the state of the current airport
     *
     * @param state the current state of the search
     *
     * @return A boolean value.
     */
    bool foundDestination(std::string state) {
        if (Airports.count(destinationAirport) == 0) {
            cout << "Specified destination does not exist" << endl;
            exit(-1);
        }
        airportsInDest = Airports.at(destinationAirport);
        return contains(state, airportsInDest);
    }

    bool contains(std::string state, vector<std::string> airports) {
        for (auto &i: airports) {
            if (state == i) {
                return true;
            }
        }
        return false;
    }

    bool contains(FlightNode node, deque<FlightNode> frontier) {
        for (auto i: frontier) {
            if (node == i) {
                return true;
            }
        }
        return false;
    }


    void bfs(std::string startCountryCity) {
        std::vector<std::string> availableAirports = Airports.at(startCountryCity);

        std::deque<shared_ptr<FlightNode>> frontier;
        std::set<std::string> visited;
        for (auto &state: availableAirports) {
            shared_ptr<FlightNode> startNode = std::make_shared<FlightNode>(state);
            if (foundDestination(startNode->getState())) {
                startNode->solutionPath();
                return;
            }
            frontier.push_back(startNode);
        }
        while (!frontier.empty()) {
            shared_ptr<FlightNode> currentAirport = frontier.front();
            frontier.pop_front();
            visited.insert(currentAirport->getState());

            if (route.count(currentAirport->getState()) == 0) continue;
            std::vector<Route> succStates = getSuccessorStates(currentAirport->getState());
            for (auto succState: succStates) {
                std::string destinationAirportCode = succState.getDestinationAirportCode();
                std::string airlineCode = succState.getAirlineCode();
                int nstops = succState.getStops();

                shared_ptr<FlightNode> childNode = make_shared<FlightNode>(airlineCode, destinationAirportCode,nstops + currentAirport->getNoOfStops(), currentAirport);
                if (visited.count(childNode->getState())==0){
                    if (foundDestination(childNode->getState())) {
                        cout << "found destination\n";
                        childNode->solutionPath();
                        return;
                    }
                    frontier.push_back(childNode);
                }
            }
        }
    }
};