/**
 * @file configuration_simulator.h
 *
 * @copyright 2019 Ziqian Qiu, All rights reserved.
 */
#ifndef SRC_CONFIGURATION_SIMULATOR_H_
#define SRC_CONFIGURATION_SIMULATOR_H_

#include <vector>
#include <list>
#include "src/config_manager.h"

class Route;
class Bus;
class Stop;

/**
 * @brief Simulator class to simulatate the system adapting configuration file
 *
 */
class ConfigSimulator {
 public:
  explicit ConfigSimulator(ConfigManager*);
  ~ConfigSimulator();
  /**
   * @brief Method to initialize simulator by taking in bus Start Timings vector
   *
   */
  void Start(const std::vector<int>&);
  /**
   * @brief Method to run the simulation
   *
   */
  void Update();

 private:
  ConfigManager* configManager_;

  std::vector<int> busStartTimings_;
  std::vector<int> timeSinceLastBus_;
  int simulationTimeElapsed_;
  std::vector<Route *> prototypeRoutes_;
  std::vector<Bus *> busses_;

  int busId = 1000;
};

#endif  // SRC_CONFIGURATION_SIMULATOR_H_
