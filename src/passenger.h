/**
 * @file passenger.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_PASSENGER_H_
#define SRC_PASSENGER_H_

#include <iostream>
#include <string>

/**
 * @brief The main class to define passenger.
 *
 */
class Passenger {
 public:
  /**
  * @brief Constructs a passenger with a standard name and id.
  *
  *
  * @param[in] int holding an id number
  * @param[in] string holding a name of a created passenger.
  *
  */
  explicit Passenger(int = -1, std::string = "Nobody");
  /**
   * @brief Method to update wait at stop
   */
  void Update();
  /**
   * @brief Passenger getting on bus
   */
  void GetOnBus();
  /**
   * @brief Total wait time on stop and on bus
   */
  int GetTotalWait() const;
  /**
   * @brief Method to decide if a passenger is on bus
   *
   * This function shows status of whether a passenger is on bus.
   *
   * @return a Boolean value
   */
  bool IsOnBus() const;
  /**
   * @brief Get destination id of the passenger
   *
   * @return integer
   */
  int GetDestination() const;
  /**
   * @brief Public reporter
   */
  void Report(std::ostream &out) const;

 private:
  std::string name_;
  int destination_stop_id_;
  int wait_at_stop_;
  int time_on_bus_;
  int id_;
  static int count_;   // global count, used to set ID for new instances
  bool on_bus_;  // If true, passenger on bus
};
#endif  // SRC_PASSENGER_H_
