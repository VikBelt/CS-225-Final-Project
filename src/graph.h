#pragma once

#include "utility.h"
#include "vertex.h"
#include <stack>
#include <functional>
#include <queue>

using std::priority_queue;
using std::stack;

namespace mtv{
    
    class Graph{
    public:

        /**
         * @brief Constructs a default Graph Variable with adjacency matrix.
         * 
         */
        Graph();

        /**
         * @brief Construct a new Graph object with a specified number of edges.
         * 
         * @param numEdges Number of Edges in the Adjacency Matrix
         */

        Graph(int numEdges);

        /**
         * @brief Method to print the First X Ammount of Verticies.
         * 
         * @param x Number of vertices to print.
         */
        void printFirstXVertices(int x);

        /*
        * Airline	2-letter (IATA) or 3-letter (ICAO) code of the airline.
        * Airline ID	Unique OpenFlights identifier for airline (see Airline).
        * Source airport	3-letter (IATA) or 4-letter (ICAO) code of the source airport.  
        * Source airport ID	Unique OpenFlights identifier for source airport (see Airport)
        * Destination airport	3-letter (IATA) or 4-letter (ICAO) code of the destination airport.
        * Destination airport ID	Unique OpenFlights identifier for destination airport (see Airport)
        * Codeshare	"Y" if this flight is a codeshare (that is, not operated by Airline, but another carrier), empty otherwise.
        * Stops	Number of stops on this flight ("0" for direct)
        * Equipment	3-letter codes for plane type(s) generally used on this flight, separated by spaces
        */ 

       /**
        * @brief Method to read in the routes.dat file and fills out the adjacency matrix accordingly.
        * 
        * @param fname Name of the file to read from.
        */
        void parseRoutes(string fname);

        /**
         * @brief Method to store airports within the graph class
         * 
         * @param filename - file holding all the airports to be used in the graph.
         */
        void storeAirports(string filename);

        /**
         * @brief Method to tell if a route exists between two Airports
         * 
         * @param srcID id of the first airport
         * @param destID id of the second airport
         * @return true if there is a route between the airports
         * @return false if there is not a route between the airports
         */
        bool checkAdjacency(int srcID, int destID);

        /**
         * @brief Get the Edges object
         * 
         * @param srcID 
         * @return vector<int> 
         */
        vector<int> getEdges(int srcID);

        /**
         * @brief Get the edge weight using the haversine formula.
         * 
         * @param source Source Airport
         * @param dest Destination Airport
         * @return double Distance between airports
         */
        double getEdgeWeight(Vertex source, Vertex dest);

        /**
         * @brief Depth First Search (DFS) using recursion. 
         * 
         * @param start Starting index for airport.
         * @param visited Vector to keep track of visited airports. 
         */
		void DFS(int start, vector<bool>& visited);

        /**
         * @brief Depth First Search (DFS) using iteration
         * 
         */
        void DFS();

        /**
         * @brief Depth First Search (DFS) 
         * 
         * @param Start Starting Node .
         * @param visited Vector to keep track of visited airports.
         * @param myfile Output file for text of traversal.
         */
        void DFS(Vertex Start, vector<bool>& visited, std::ofstream* myfile);

        /**
         * @brief Returns a vector of all the vertices in the graph.
         * 
         * @return vector<Vertex> the vector of all the airports in the graph
         */
        vector<Vertex> getVerticies() const;

        /**
         * @brief Method to figure out the landmark path using the shortest path between three paths.
         * 
         * @param start 
         * @param mid 
         * @param end 
         * @return vector<Vertex> 
         */
        vector<Vertex> landmarkPath(Vertex start, Vertex mid, Vertex end);

        /**
         * @brief Method to determine the shortest path between two airports in the airport graph with Dijkstra's Algorithm.
         * 
         * @param start Starting Vertex in the Path
         * @param end Ending Vertex in the Path
         * @param path Vector of airports in the shortest path
         * @return true If there is a shortest path between the two verticies
         * @return false If there is not a shortes parth between the two verticies
         */
        bool shortestPath(Vertex start, Vertex end, vector<Vertex>& path);

    private:
        
        /**
         * @brief Helper function for parseRoutes
         * 
         * @param routesFile Reference to an ifstream object, for the input route file 
         * @param line Reference to a string - see graph.cpp
         * @param item Reference to a string - see graph.cpp
         */
        void parseRoutesHelper(std::ifstream& routesFile, string& line, string& item);

        /**
         * @brief Helper function for storeAirports
         * 
         * @param routesFile Reference to an ifstream object, for the input route file 
         * @param line Reference to a string - see graph.cpp.
         */
        void storeAirportsHelper(std::ifstream& routesFile, string& line);

        /*
         * Adjacency Matrix holds the route (edge) information
         * The matrix is of size m^2 where m is the # of edges 
         * The row represents the departure airport (vertex) and the column represents the 
         * arrival airport
         * 
         * The index is the the airport ID, there are gaps but it is recorded as no edge
         */
        vector<vector<double>> adjMat;

        //structure to hold all the airports (verticies)
        vector<Vertex> airports;
    };

} //namespace mtv
