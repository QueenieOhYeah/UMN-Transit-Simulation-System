#include <ctime>
#include <iostream>
#include <random>
#include <fstream>

#include "local_simulator.h"

int main(int argc, char *argv[]) {
  using namespace std;
  cout << "program name: " << argv[0] << endl;
  cout << "number of args " << argc << endl;

  if (argc == 1) cout << "no args" << endl;
  else if (argc == 2) cout << "file name: " << argv[1] << endl;

  ofstream of_ptr;
  of_ptr.open(argv[1]);

  if (of_ptr.is_open()) {
    of_ptr << "The file is " << argv[1] << endl;

    int rounds = 50; //Number of rounds of generation to simulate in test

    srand((long)time(NULL)); //Seed the random number generator...

    LocalSimulator my_sim;

    of_ptr << "/*************************" << std::endl << std::endl;
    of_ptr << "         STARTING" << std::endl;
    of_ptr << "        SIMULATION" << std::endl;
    of_ptr << "*************************/" << std::endl;

    my_sim.Start(static_cast<std::ostream&>(of_ptr));

    of_ptr << "/*************************" << std::endl << std::endl;
    of_ptr << "           BEGIN" << std::endl;
    of_ptr << "          UPDATING" << std::endl;
    of_ptr << "*************************/" << std::endl;

    for (int i = 0; i < rounds; i++) {
      my_sim.Update(static_cast<std::ostream&>(of_ptr));
    }

    of_ptr << "/*************************" << std::endl << std::endl;
    of_ptr << "        SIMULATION" << std::endl;
    of_ptr << "         COMPLETE" << std::endl;
    of_ptr << "*************************/" << std::endl;
    of_ptr.close();
  } else {
    cout << "The file is not open" << endl;
  }
  return 0;
}
