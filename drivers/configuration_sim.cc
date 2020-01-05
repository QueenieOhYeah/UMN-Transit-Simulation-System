/**
 * @file configuration_sim.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include <iostream>

#include "src/config_manager.h"
#include "src/configuration_simulator.h"

int main(int argc, char**argv) {
  using namespace std;
  //configuration
  const int numTimeSteps = 20;
  const std::vector<int>& busStartTimings{5, 10, 15};

  cout << "program name: " << argv[0] << endl;
  cout << "number of args " << argc << endl;

  if (argc > 2) {
    std::cout << "Usage: ./build/bin/configuration_sim <config_filename>";
    std::cout << std::endl;
    return 0;
  }
  ConfigManager* cm = new ConfigManager();
  std::string filename = "config.txt";
  if (argc == 2) {
    filename = argv[1];
  }
  cout << filename << endl;
  int result = cm->ReadConfig(filename);
  if (result == 0) {
    cout << "Fail to open file " <<  filename << endl;
    return 0;
  }
  ConfigSimulator cs(cm);
  cs.Start(busStartTimings);
  for (int i = 0; i < numTimeSteps; i++) {
    cs.Update();
  }
  // NOTE: this usage will change depending on
  //       how you build your config_sim classes
  //   E.g., how will you handle getting the length of simulation value?

  // Check command line params for config file name

  // if filename arg present
  //   Create ConfigManager
  //   Call ReadConfig
  //   Create ConfigurationSimulator
  //   Call Start on ConfigurationSimulator
  //   Start for loop, length of simulation (where from?)
  //     Call Update on ConfigurationSimulator
  // else
  //   echo info to the user about needing a config file name

  return 0;
}
