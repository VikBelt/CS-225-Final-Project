#pragma once

#include "utility.h"

namespace mtv {

    /**
     * A Class to store an airport's data 
     * Airports will be used as the verticies in the Graph seen in graph.h
     * 
     */
    class Vertex {
    public:
        //Constuctors
        Vertex();
        Vertex(int, string, string, string, double, double);
        //Airport Data
        int airportId;
        string airportName;
        string IATA_CODE;
        string ICAO_CODE;
        double longitude;
        double latitude;
        //overload the << operator to print the Vertex
        friend std::ostream& operator<<(std::ostream& os, const Vertex& source);
        friend bool operator !=(const Vertex& rhs, const Vertex& lhs);
        bool operator ==(const Vertex& other);
    };

}//namespace mtv  