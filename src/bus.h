/**
 * @file bus.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_BUS_H_
#define SRC_BUS_H_

#include <iostream>
#include <list>
#include <string>

#include "src/passenger.h"
#include "src/route.h"
#include "src/stop.h"
#include "src/data_structs.h"

class PassengerUnloader;
class PassengerLoader;
class Route;
class Stop;

/**
 * @brief The main class to define bus.
 *
 */

class Bus {
 public:
  /**
  * @brief Constructs a bus with a standard name, two route pointers, passenger capacity and speed.
  *
  * @param[in] string holding a name of a bus.
  * @param[in] Route * pointing to an outgoing route.
  * @param[in] Route * pointing to an incoming route.
  * @param[in] int holding the capacity.
  * @param[in] double holding the speed.
  *
  */
  Bus(std::string name, Route * out, Route * in, int capacity = 60,
                                                 double speed = 1);

  bool LoadPassenger(Passenger *);
  /**
   * @brief Method to decide if the bus is moving
   *
   * If not moving, it reaches to a stop
   *
   * @return a Boolean value
   */
  bool Move();
  /**
   * @brief Method to update the status of bus
   *
   * It update the distance to next stop, indicators to next stop, status of every passenger on bus
   * It involves load and unload passengers at stops
   *
   */
  void Update();
  void Report(std::ostream &out);
  /**
   * @brief Method to indicate if the bus complete all routes
   *
   */
  bool IsTripComplete();
  /**
   * @brief Method to unload passenger to a stop
   * @return a integer indication the number of passengers unloaded
   */
  int UnloadPassengers(Stop * stop);
  /**
   * @brief Method to update bus data
   *
   */
  void UpdateBusData();
  /**
   * @brief Getter of bus data
   *
   */
  BusData GetBusData();
  /**
   * @brief Getter of bus name
   * @return a string
   */
  std::string GetName() const;
  /**
   * @brief Getter of pointer to next stop
   */
  Stop * GetNextStop();
  /**
   * @brief Getter of pointer to previous stop
   */
  Stop * GetPreviousStop();
  /**
   * @brief Getter of number of passengers on bus
   * @return size_t
   */
  size_t GetNumPassengers();
  /**
   * @brief Getter of pointer to bus capacity
   */
  int GetCapacity();

 private:
  std::list<Passenger *> passengers_;
  int passenger_max_capacity_;
  std::string name_;
  double speed_;  // could also be called "distance travelled in one time step"
  Route * outgoing_route_;
  Route * incoming_route_;
  double distance_remaining_;  // when negative?, unload/load procedure occurs
                              // AND next stop set
  BusData bus_data_;
  // double revenue_; // revenue collected from passengers, doesn't include
                      // passengers who pay on deboard
  // double fuel_;   // may not be necessary for our simulation
  // double max_fuel_;
};
#endif  // SRC_BUS_H_
