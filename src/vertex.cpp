
#include "vertex.h"

namespace mtv {

    /**
     * @brief Constructs a default vertex.
     * 
     * A Vertex stores an airport with position, name and codes. 
     */

    Vertex::Vertex() {
        airportId = NO_EDGE;
        longitude = 0.0;
        latitude = 0.0;
        airportName = "";
        IATA_CODE = "";
        ICAO_CODE = "";
    }

    /**
     * @brief Construct a new Vertex Object Given parameters.
     * 
     * @param id 
     * @param name 
     * @param codeOne 
     * @param codeTwo 
     * @param lat 
     * @param m_long 
     */

    Vertex::Vertex(int id, string name, string codeOne, string codeTwo, double lat, double m_long)
    {
        airportId = id;
        airportName = name;
        IATA_CODE = codeOne;
        ICAO_CODE = codeTwo;
        latitude = lat;
        longitude = m_long; 
    }

    /**
     * @brief Operator Overload of << to print a Vertex's content to the console. 
     * 
     * @param os 
     * @param source
     * @return std::ostream& 
     */

    std::ostream& operator<<(std::ostream& os, const Vertex& source) {
        os << "Airport ID: " << source.airportId << ", Name: " << source.airportName << ", IATA: " << source.IATA_CODE
            << ", ICAO: " << source.ICAO_CODE << ", Lat: " << source.latitude << ", Long: " << source.longitude;
        return os;
    }

    /**
     * @brief Overload of == to compare Equality
     * 
     * @param other 
     * @return true 
     * @return false 
     */

    bool Vertex::operator ==(const Vertex& other) {
        //if airport name and id are equal then two airports are equal
        if(this->airportId == other.airportId && this->airportName == other.airportName){
            return true;
        }
        else
            return false;
    }

    /**
     * @brief Overload of != to compare Equality
     * 
     * @param lhs 
     * @param rhs 
     * @return true - if not Verticies are not equal
     * @return false - if Verticies are equal
     */

    bool operator !=(const Vertex& lhs, const Vertex& rhs) {
        if(lhs.airportId == rhs.airportId && lhs.airportName == rhs.airportName){
            return false;
        }
        else
            return true;
    }

} //namespace mtv