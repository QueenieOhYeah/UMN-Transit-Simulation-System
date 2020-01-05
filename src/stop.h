/**
 * @file stop.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_STOP_H_
#define SRC_STOP_H_

#include <list>
#include <iostream>
#include <string>

#include "src/bus.h"
#include "src/passenger.h"

class Bus;
/**
 * @brief The main class to define stop.
 *
 */
class Stop {
 public:
   /**
   * @brief Constructs a stop with latitude and longitude.
   *
   */
  explicit Stop(int, double = 44.973723, double = -93.235365);
  /**
   * @brief Get if of the stops_
   *
   * @return id of the stop
   */
  int GetId() const;
  /**
   * @brief Method to add passengers to the stop.
   *
   * This function adds passengers to the stop.
   *
   * @return the number of passenger added which is 1 if successfully added.
   */
  int AddPassengers(Passenger *);
  void Update();
  void Report(std::ostream &out) const;
  /**
   * @brief Method to load passenger on bus.
   *
   * @return the number of passenger loaded on bus.
   */
  int LoadPassengers(Bus * bus);
  /**
   * @brief Getter of longitude
   *
   * @return double
   */
  double GetLong();
  /**
   * @brief Getter of latitude
   *
   * @return double
   */
  double GetLat();
  /**
   * @brief Getter of stop name
   *
   * @return string
   */
  std::string GetName();
  /**
   * @brief Getter of number of passengers
   *
   * @return size_t
   */
  size_t GetNumPassengers();

 private:
  int id_;
  std::list<Passenger *> passengers_;  // considered array, vector, queue, list
  double longitude_;
  double latitude_;  // are we using long/lat coords?
  // derived information - not needed depending on passengers_
  // data structure implementation?
  // int passengers_present_;
};
#endif  // SRC_STOP_H_
