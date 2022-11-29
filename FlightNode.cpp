#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <sstream>
#include <memory>

using std::shared_ptr;
using std::make_shared;

class FlightNode {
private:
    std::string airlineCode;
    std::string state;
    int noOfStops;
    shared_ptr<FlightNode> sourceAirport;
public:
    FlightNode(std::string AirlineCode, std::string State, int stops,  shared_ptr<FlightNode> parent) {
        this->airlineCode = AirlineCode;
        this->state = State;
        this->noOfStops = stops;
        this->sourceAirport = parent;
    }

    FlightNode(std::string State) {
        this->state = State;
        this->airlineCode = "";
        this->sourceAirport = nullptr;
        this->noOfStops = 0;
    }

    /**
     * It returns the number of stops in the route
     *
     * @return The number of stops.
     */
    int getNoOfStops() {
        return this->noOfStops;
    }

    /**
     * This function returns the airline code
     *
     * @return The airline code.
     */
    std::string getAirlineCode() {
        return this->airlineCode;
    }

    /**
     * This function returns the state of the object
     *
     * @return The state variable is being returned.
     */
    std::string getState() {
        return this->state;
    }

    /**
     * This function returns the sourceAirport
     *
     * @return The sourceAirport variable is being returned.
     */
    shared_ptr<FlightNode> getSourceAirport() {
            return this->sourceAirport;
    }

    /**
     * The function returns true if the airlineCode, state, noOfStops and sourceAirport of the two FlightNodes are equal
     *
     * @param rhs The right hand side of the operator.
     *
     * @return a boolean value.
     */
    bool operator==(const FlightNode &rhs) const {
        return airlineCode == rhs.airlineCode &&
               state == rhs.state &&
               noOfStops == rhs.noOfStops;
    }

    /**
     * It checks if the flight number is not equal to the flight number of the flight node.
     *
     * @param rhs The right hand side of the operator.
     *
     * @return The boolean value of the comparison of the two FlightNodes.
     */
    bool operator!=(const FlightNode &rhs) const {
        return !(rhs == *this);
    }

    /**
     * This function is used to write the solution path to a file
     */
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
        shared_ptr<FlightNode> current = make_shared<FlightNode>(this->airlineCode, this->state, this->noOfStops,
                                                                 this->sourceAirport);
        /* Getting the source airport of the current node and then pushing it to the solution vector. */
        while (current->sourceAirport != nullptr) {
            path = current->getAirlineCode() + " from " + current->getSourceAirport()->getState() + " to " +
                   current->state + " " + std::to_string(current->noOfStops) + " stops";
            std::cout << path << std::endl;
            solution.push_back(path);
            current = current->sourceAirport;
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
            return;
        }
        catch (std::invalid_argument &e) {
            std::cerr << e.what() << std::endl;
            exit(-1);
        }
  }
};


