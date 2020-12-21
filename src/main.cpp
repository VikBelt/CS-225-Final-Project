#include "graph.h"
using namespace mtv;

int main(){
    // Generates graph and reserves space for 20000 edges
    std::cout<<"Creating Graph (takes a few seconds)"<<std::endl;
    Graph testGraph(20000);
    std::cout<<"Graph construction complete"<<std::endl;

    // parse in information about routes and airports
    std::cout<<"Parsing in routes"<<std::endl;
    try{
        testGraph.parseRoutes("routes_parsed.csv");
    } 
    catch (const mtv::graph_excepts::route_parse_error& error ){
        std::cout<<error.what()<<std::endl;
    }
    std::cout<<"Route parsing complete"<<std::endl;

    //store airport info
    std::cout<<"Parsing in airport info"<<std::endl;
    try{
        testGraph.storeAirports("airports.dat");
    }
    catch(mtv::graph_excepts::airport_parse_error& error){
        std::cout<<error.what()<<std::endl;
    }
    std::cout<<"Airport parsing complete"<<std::endl;

    // get a vector of airports to facilitate calling functions
    vector<Vertex> airports = testGraph.getVerticies();

    std::cout<<std::endl;

    // commencing main demonstration
    std::cout<<"Performing iterative DFS across all components"<<std::endl;
    testGraph.DFS();
    std::cout<<"output saved in 'traversal.txt'"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Performing recursive DFS commencing from Koné Airport, New Caledonia"<<std::endl;
    vector<bool> visited(mat_t, false);
    testGraph.DFS(1998,visited);
    std::cout<<std::endl;
    std::cout<<"DFS complete"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Finding Shortest Path from Port Moresby Jacksons International Airport in Papua New Guinea to Barnaul Airport, Russia"<<std::endl;
    vector<Vertex> shortest_path;
    testGraph.shortestPath(airports[5], airports[2956], shortest_path);
    std::ofstream myfile;
    myfile.open ("ShortestPath.txt");
    myfile<<"Start: ";
    for(auto elem: shortest_path){
        myfile<<elem.airportName<<" -> "<<std::endl;
    }
    myfile<<"Journey Complete";
    myfile.close();
    std::cout<<"Shortest_path saved in ShortestPath.txt"<<std::endl;
    std::cout<<std::endl;

    std::cout<<"Want to see the pyramids before heading home for spring break..."<<std::endl;
    std::cout<<"Finding Landmark Path from University of Illinois Willard Airport to O'Hare through Cairo"<<std::endl;
    vector<Vertex> landmark_path;
    landmark_path = testGraph.landmarkPath(airports[4049],airports[1128],airports[3830]);

    std::ofstream f2;
    f2.open ("LandMarkPath.txt");
    f2<<"Start: ";
    for(auto elem: landmark_path){
        f2<<elem.airportName<<" -> "<<std::endl;
    }
    f2<<"Journey Complete";
    f2.close();
    std::cout<<"landmark_path saved in LandMarkPath.txt"<<std::endl;

    std::cout<<std::endl;
    std::cout<<"Demo Complete"<<std::endl;
    return 0;
}

 