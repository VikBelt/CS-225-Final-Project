#include "utility.h"

namespace mtv {
    //Math Helper Functions
    double radians(const double degrees){
        double rad =  (M_PI * degrees) / 180;
        return rad;
    }

    //calculate distance between two points on Earth
    double calculateDistance (double srcLat, double srcLong, double destLat, double destLong) {
        //convert to degrees
        srcLat = radians(srcLat);
        srcLong = radians(srcLong);
        destLat = radians(destLat);
        destLong = radians(destLong);
        //implement the Haversine formula for distance
        double deltaLong = destLong - srcLong;
        double deltaLat = destLat -  srcLat;
        double result = pow(sin(deltaLat/2),2) + cos(srcLat) * cos(destLat) * pow(sin(deltaLong/2),2);
        result = 2 * asin(sqrt(result));
        result *= R_EARTH;
        return result; 
    }
    
} //namespace mtv
