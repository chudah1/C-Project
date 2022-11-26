#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>


class FlightNode{
    private:
        std::string airlineCode;
        std::string state;
        int noOfStops;
         FlightNode* sourceAirport;
public:
    FlightNode(std::string AirlineCode, std::string State, int stops, FlightNode* parent){
        airlineCode = AirlineCode;
        state = State;
        noOfStops = stops;
        sourceAirport = parent;
    }

    FlightNode(std::string State){
        state = State;
        airlineCode="";
        sourceAirport= NULL;
        noOfStops=0;
    }

    int getNoOfStops() {
        return noOfStops;
    }

    std::string getAirlineCode(){
        return airlineCode;
    }

    std::string getState(){
        return state;
    }

    FlightNode *getSourceAirport(){
        return sourceAirport;
    }

    void solutionPath(){
        std::string startCity = "";
        std::string destinationCity="";
        try {
            ifstream inputFile("london-banjul.txt");
            getline(inputFile, startCity, ',');
            getline(inputFile, destinationCity, ',');
        }
        catch (std::invalid_argument& e) {
            cerr<<e.what() <<endl;
            exit(-1);
        }
        std::vector<std::string> solution;
        std::string path="";
        FlightNode current = *this;

        while(current.sourceAirport!=NULL){
           path= current.getAirlineCode() + " from " + current.getSourceAirport()->getState() + " to " + current.getState() + " "+std::to_string(current.getNoOfStops()) + " stops";
           solution.push_back(path);
           current = *current.getSourceAirport();
        }
        std::reverse(solution.begin(), solution.end());
        
        try{
            ofstream pathFile(startCity + "-" + destinationCity +"_" + "output.txt");
            int number = 1;
            for (auto &solutionpath : solution) {
                pathFile<<(number +". " + solutionpath);
                number++;
            }
            pathFile<<"Total flights: " + solution.size();
            pathFile<<"Total additional stops: " + noOfStops;
            pathFile<<"Optimality Criteria: Flights";
            pathFile.close();

        }
        catch (std::invalid_argument& e) {
            cerr<<e.what() <<endl;
            exit(-1);
        }

    }


};

