/**
 * @file random_passenger_generator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_RANDOM_PASSENGER_GENERATOR_H_
#define SRC_RANDOM_PASSENGER_GENERATOR_H_

#include <list>
#include <random>
#include <ctime>

#include "src/passenger_generator.h"
#include "src/stop.h"

class Stop;  // forward declaration
/**
 * @brief The main class for the generation of passengers.
 *
 * This function has parameters of a list of probability that a passenger appears at certain stop
 * and a list of pointer to the stops correspondingly.
 * Calls to \ref GeneratePassengers function generate passengers in stops.
 */
class RandomPassengerGenerator : public PassengerGenerator{
 public:
  RandomPassengerGenerator(std::list<double>, std::list<Stop *>);
  /**
   * @brief Generation of a passenger with a randomized name and random destination within bounds.
   *
   * With the random name from Passenger Factory, generate passengers in stops based on probability.
   * @return the number od passengers that are generated.
   */
  int GeneratePassengers() override;

 private:
  static std:: minstd_rand0 my_rand;
};

#endif  // SRC_RANDOM_PASSENGER_GENERATOR_H_
