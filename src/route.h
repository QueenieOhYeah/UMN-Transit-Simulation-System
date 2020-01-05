/**
 * @file route.h
 *
 * @Copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROUTE_H_
#define SRC_ROUTE_H_

#include <list>
#include <iostream>
#include <string>

#include "./passenger_generator.h"
#include "./stop.h"
#include "./data_structs.h"

class PassengerGenerator;
class Stop;
/**
 * @brief The main class to define route.
 *
 */

class Route {
 public:
   /**
   * @brief Constructs a route.
   *
   *
   * @param[in] string holding a name of a created route.
   * @param[in] Stop ** holding the stops the route involves.
   * @param[in] double * holding distances between the stops.
   * @param[in] int holding the number of stops
   */
  Route(std::string name, Stop ** stops, double * distances, int num_stops,
        PassengerGenerator *);
  /**
  * @brief Copy a route.
  */
  Route * Clone();
  void Update();
  void Report(std::ostream&);
  /**
  * @brief Decide if a route is finished.
  */
  bool IsAtEnd() const;
  /**
  * @brief Change destination_stop_ to next stop.
  */
  void NextStop();  // Change destination_stop_ to next stop

  /**
  * @brief Get pointer to next stop.
  * @return a pointer to next stop
  */
  Stop * GetDestinationStop() const;    // Get pointer to next stop
  // double GetTotalRoteDistance() const;
  /**
  * @brief Get distance to next stop.
  * @return distance to next stop
  */
  double GetNextStopDistance();
  /**
  * @brief Get pointer to next stop
  * @return pointer to next stop
  */
  Stop * GetNextStop();
  /**
  * @brief Get pointer to previous stop
  * @return pointer to previous stop
  */
  Stop * GetPreviousStop();
  /**
  * @brief Get name of the route
  * @return string
  */
  std::string GetName();
  /**
  * @brief list of stops
  * @return list of stops
  */
  std::list<Stop *> GetStops();
  /**
  * @brief Update route data
  */
  void UpdateRouteData();
  /**
  * @brief Getter of route data
  */
  RouteData GetRouteData();

 private:
  int GenerateNewPassengers();       // generates passengers on its route
  PassengerGenerator * generator_;
  std::list<Stop *> stops_;
  std::list<double> distances_between_;  // length = num_stops_ - 1
  std::string name_;
  int num_stops_;
  RouteData route_data_;
  int destination_stop_index_;  // always starts at zero, no init needed
  Stop * destination_stop_;
  Stop * previous_stop_;
  // double trip_time_; // derived data - total distance travelled on route
};
#endif  // SRC_ROUTE_H_
