/**
 * @file local_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_LOCAL_SIMULATOR_H_
#define SRC_LOCAL_SIMULATOR_H_

#include <vector>

#include "src/simulator.h"
/**
 * @brief The main class to simulate the transit system.
 *
 * Calls to \ref Start function to prepare necessary data structures.
 * \ref Update function to start simulation.
 */
class LocalSimulator : public Simulator {
 public:
  bool Start(std::ostream& out) override;
  bool Update(std::ostream& out) override;
 private:
  std::vector<int> bus_counters_;
  std::vector<int> bus_start_timings_;
  std::vector<int> time_since_last_bus_generation_;
  int simulation_time_elapsed_;
};

#endif  // SRC_LOCAL_SIMULATOR_H_
