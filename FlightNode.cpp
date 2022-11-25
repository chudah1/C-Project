#include <iostream>
#include <string>
#include <algorithm>


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
            
        }
        catch (...) {
            
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
            
        }
        catch (...) {
            
        }

    }


};

