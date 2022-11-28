#include <string>
#include "BFS.cpp"


int main() {
    std::ifstream inputFile(
            R"(C:\Users\ohene\OneDrive\Documents\School Work\Assignments\Intermediate Computer Programming\C++\C-Project\london-banjul.txt)");
    string startAirport;
    string destinationAirport;
    std::getline(inputFile, startAirport);
    std::getline(inputFile, destinationAirport);
    Main test(destinationAirport);
    test.bfs(startAirport);
    return 0;

}