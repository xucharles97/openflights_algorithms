#pragma once
#include <cmath>
#include <math.h>

#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double degreesToRadians(double degrees) { return (degrees * M_PI / 180); }

//  This function converts radians to decimal degrees
double rad2deg(double rad) { return (rad * 180 / M_PI); }

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceLatLng(double lat1d, double lon1d, double lat2d, double lon2d) {
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = degreesToRadians(lat1d);
    lon1r = degreesToRadians(lon1d);
    lat2r = degreesToRadians(lat2d);
    lon2r = degreesToRadians(lon2d);
    u = sin((lat2r - lat1r) / 2);
    v = sin((lon2r - lon1r) / 2);
    return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}