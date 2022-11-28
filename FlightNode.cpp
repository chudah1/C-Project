#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <sstream>

class FlightNode {
private:
    std::string airlineCode;
    std::string state;
    int noOfStops;
    FlightNode *sourceAirport;
public:
    FlightNode(std::string AirlineCode, std::string State, int stops, FlightNode *parent) {
        airlineCode = AirlineCode;
        state = State;
        noOfStops = stops;
        sourceAirport = parent;
    }

    FlightNode(std::string State) {
        state = State;
        airlineCode = "";
        sourceAirport = NULL;
        noOfStops = 0;
    }

    int getNoOfStops() {
        return noOfStops;
    }

    std::string getAirlineCode() {
        return airlineCode;
    }

    std::string getState() {
        return state;
    }

    FlightNode *getSourceAirport() {
        return sourceAirport;
    }

    bool operator==(const FlightNode &rhs) const {
        return airlineCode == rhs.airlineCode &&
               state == rhs.state &&
               noOfStops == rhs.noOfStops &&
               sourceAirport == rhs.sourceAirport;
    }

    bool operator!=(const FlightNode &rhs) const {
        return !(rhs == *this);
    }

    void solutionPath() {
        std::string startCity;
        std::string destinationCity;
        try {
            std::string readLine;
            std::ifstream inputFile(
                    R"(C:\Users\ohene\OneDrive\Documents\School Work\Assignments\Intermediate Computer Programming\C++\C-Project\london-banjul.txt)");
            std::vector<std::string> inputData;
            while (getline(inputFile, readLine)) {
                inputData.push_back(readLine);
            }
            std::stringstream ss(inputData[0]);
            std::getline(ss, readLine, ',');
            inputData[0] = readLine;
            startCity = inputData[0];
            std::stringstream s(inputData[1]);
            std::getline(s, readLine, ',');
            inputData[1] = readLine;
            destinationCity = inputData[1];
        }
        catch (std::invalid_argument &e) {
            std::cerr << e.what() << std::endl;
            exit(-1);
        }
        std::vector<std::string> solution;
        std::string path;
        FlightNode current = *this;

        while (current.sourceAirport != NULL) {
            path = current.getAirlineCode() + " from " + current.getSourceAirport()->getState() + " to " +
                   current.getState() + " " + std::to_string(current.getNoOfStops()) + " stops";
            solution.push_back(path);
            current = *current.getSourceAirport();
        }
        std::reverse(solution.begin(), solution.end());

        try {
            std::ofstream pathFile(startCity + "-" + destinationCity + "_" + "output.txt");
            int number = 1;
            for (auto &solutionpath: solution) {
                pathFile << (std::to_string(number) + ". " + solutionpath) + "\n";
                number++;
            }
            pathFile << "Total flights: " + std::to_string(solution.size()) + "\n";
            pathFile << "Total additional stops: " + std::to_string(noOfStops) + "\n";
            pathFile << "Optimality Criteria: Flights \n";
            pathFile.close();

        }
        catch (std::invalid_argument &e) {
            std::cerr << e.what() << std::endl;
            exit(-1);
        }
    }
};


