/**
 * @file bus.h
 *
 * @copyright 2019 Ziqian Qiu, All rights reserved.
 */
#ifndef SRC_DATA_STRUCTS_H_
#define SRC_DATA_STRUCTS_H_

#include <string>
#include <vector>

/**
 * @brief Structure for position
 *
 */
struct Position {
    Position() : x(0), y(0) {}
    float x;
    float y;
};

/**
 * @brief Structure for bus data used for visualization simulation
 *
 */
struct BusData {
    BusData() : id(""), position(Position()), num_passengers(0), capacity(0) {}
    std::string id;  // some unique identifier for the bus
    Position position;  // long lat position of bus
    int num_passengers;
    int capacity;
};
/**
 * @brief Structure for stop data used for visualization simulation
 *
 */
struct StopData {
    StopData() : id(""), position(Position()), num_people(0) {}
    std::string id;  // some unique identifier for the stop
    Position position;  // long lat position of bus
    int num_people;
};
/**
 * @brief Structure for route data used for visualization simulation
 *
 */
struct RouteData {
    RouteData() : id(""), stops(std::vector<StopData>(0)) {}
    std::string id;  // some unique identifier for the route
    std::vector<StopData> stops;
};

#endif  // SRC_DATA_STRUCTS_H_
