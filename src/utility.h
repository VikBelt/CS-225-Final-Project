#pragma once

#include <exception>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <cmath>

using std::vector;
using std::string;
using std::sqrt;
using std::asin;
using std::sin;
using std::cos;
using std::pow;

/**
 * @brief namespace for all project contents
 * 
 */
namespace mtv {
    //constants used throughout the project
    constexpr int mat_t = 15000; //default matrix size
    constexpr double NO_EDGE = -1; //empty matrix value
    constexpr double R_EARTH = 6371.0;
    constexpr double loadFactor = 0.25; // what % of vertices does this vertex connect to
    constexpr double INF = std::numeric_limits<double>::infinity();

    /**
     * @brief Function to convert degrees to radians
     * 
     * @param degrees Angle in Degrees
     * @return double Angle in Radians
     */
    double radians(const double degrees);

    /**
     * @brief Function to implement the haversine formula to calculate the distance between two points on earth.
     * 
     * @param srcLat Source Latitude
     * @param srcLong Source Longitude
     * @param destLat  Destination Latitude
     * @param destLong Destination Longitude
     * @return double Distance in km.
     */
    double calculateDistance (double srcLat, double srcLong, double destLat, double destLong);

    //exception handling classes
    /**
     * @brief namespace for exception handling classes
     * 
     */
    namespace graph_excepts {
        /**
         * @brief Class for route parsing error. 
         * 
         */
        class route_parse_error : public std::exception {
        public:
            route_parse_error(string error) : error_{error} {}
            /**
             * @brief function to return error message - from std::exception
             * 
             * @return const char* error message
             */
            const char* what() const noexcept override {
                return error_.c_str();
            }
        private:
            string error_; //error message
        };

        /**
         * @brief Class for airport parsing error
         * 
         */
        class airport_parse_error : public std::exception {
        public:
            airport_parse_error(string error) : error_{error} {}
            /**
             * @brief function to return error message - from std::exception
             * 
             * @return const char* error message
             */
            const char* what () const noexcept override {
                return error_.c_str();
            }
        private:
            string error_;
        };

    } //namespace errorhandling

} //namespace mtv