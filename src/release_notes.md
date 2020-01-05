### Release Note
There are 2 refactored versions of the program which are in branch `refactor/iter2` and `refactor/iter2` respectively.

#### Refactor 1
Refactor 1 exists in branch refactor/iter2.
The version on the master/devel branch involves a problem that the probability list for stops includes the value for the final stop on a route which is not guaranteed to be 0, since it is decided by the configuration file. However, with nowhere to go, that probability needs to be 0. Therefore, this version of code will ignore the possibility of the final stop on a route when it is not specified as 0 in the configuration file.

#### Refactor 2
Refactor 2 exists in branch refactor/iter3.
This version is refactored by extracting 3 functions from the Update() function located in configuration_sim.cc.
The functions extracted are:
    • GenBus() on line 97 in configuration_sim.cc aims at generateing busses.
    • UpdateRoute() on line 115 in configuration_sim.cc aims at updating routes.
    • UpdateBus() on line 124 in configuration_sim.cc aims at updating busses.
The Update() function is doing the job of generating bus when necessary, updating the status of all routes and updating the busses. So I defined 3 additional functions to specify on each of the job for the reason that it shortens the original update function and makes it more readable for other potential developers.

#### Regression test
1. I modified the r_local_simulation file that uses 3 stops respectively for eastbound and westbound in the `Start` method, so the driver runs faster.
2. I modified the rtest_passenger_generator file so that it the number of passengers created in each time step is equal to the id of the stop.
3. I created a seperate deterministic_passenger_factory class that produces a deterministic name.
