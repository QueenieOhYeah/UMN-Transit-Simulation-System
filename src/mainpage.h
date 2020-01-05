/**
 * @file mainpage.h
 *
 * @copyright 2019 Ziqian Qiu, All rights reserved.
 */

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_
/*! \mainpage Project mainpage
 *
 * This webpage is for CSCI3081W individual project that developed in University of Minnesota.
 * Copy right to Ziqian Qiu & University of Minnesota.
 *
 * \section intro_sec Introduction
 * The goal of this software project is to develop a rudimentary transit simulator
 * in which simulations can be controlled via external configuration and be visualized within a graphics window.
 * In the first iteration,
 * we will limit the simulation to a single scenario involving campus
 * transit via bus here at the University of Minnesota.
 *
 * One of the very important design fot this project is to separate the graphics from the simulator.
 * This allows us programmers to implement the basic functionality at the beginning and then embed the graphic
 * into the program. Different modes are offered for users to freely selected from to report the raw data or to visualize the data graphically.
 *
 * \subsection user For Users
 * \ref page1
 *
 * \subsection dev For Developers
 * \ref page2
 *
 *
 */

/*! \page page1 User Guide
* \section d Download
* Click the green button labelled download at my github repository at <a href="https://github.umn.edu/umn-csci-3081-f19/repo-qiuxx283">Click here</a> .
* The program is located in the project directory.
* \section s Steps to run the Simulators
* \subsection c Compile the program
* 1. Open the terminal in your own machine, direct to the project directory. Type "make" to compile the program.
* \subsection r Run the Visualization Simulation
* The visualization simulation relies on files in Lab machines, therefore connection to Lab mechines in the University of
* Minnesota is required to run the visualization simulation.
* \subsubsection Step by step for CSE Labs or vole users
* 1. Navigate to base project directory(project/) \n
* 2. Start server by entering "./build/bin/vis_sim <port_number>" in your terminal. \n
* *Notice: <port_number> can be anything. Try and pick numbers above 8000 and not multiples of 10.
* *Notice: You must run by doing ./build/bin/vis_sim <port_number>. You cannot cd to bin/ and run ./vis_sim <port_number>. \n
* 3. Navigate to the following address on your VOLE browser (Firefox/Chrome): \n
* http://127.0.0.1:<port_number>/web_graphics/project.html
*
* \subsubsection Step by step for ssh users
* You can SSH using a Windows machine with Git Bash: ssh -L <port number>:127.0.0.1:<port_number> <x500>@<cse_labs_computer>.cselabs.umn.edu
* 1. Navigate to base project directory(project/) \n
* 2. Start server by entering "./build/bin/vis_sim <port_number>" in your terminal. \n
* *Notice: <port_number> can be anything. Try and pick numbers above 8000 and not multiples of 10.
* *Notice: You must run by doing ./build/bin/vis_sim <port_number>. You cannot cd to bin/ and run ./vis_sim <port_number>. \n
* 3. Navigate to the following address on your LOCAL machine using your LOCAL browser (Firefox/Chrome): \n
* http://127.0.0.1:<port_number>/web_graphics/project.html
*
* \subsection r Run the Configuration Simulation
* The program provides a simulator that enables the users to specified the features of the domain elements in the program involving
* busses, routes and stops. Since it is not using visualized graphics, it is not necessary to connect to the Lab machine in the University of Minnesota.
* \subsubsection r1 Run the default congifuration simulation
* 1. Navigate to base project directory(project/) \n
* 2. Start server by entering "./build/bin/config_sim" in your terminal. Then you will see the simulation results printed on the terminal. \n
* \subsubsection a Add your own configuration and run the simulator
* 1. Navigate to project/config directory
* 2. Create your own configuration file and save in the directory as .txt \n
* Format of the configuration file: \n
* ROUTE_GENERAL, <Bus_name> \n
* ROUTE, <Route_named> \n
* STOP, <stop_name>, <stop_longitute>, <stop_latitute>, <passenger_generation_probabilities> \n
* (Multiple stops) \n
* ROUTE, <route_name> \n
* STOP, <stop_name>, <stop_longitute>, <stop_latitute>, <passenger_generation_probabilities> \n
* (Multiple stops) \n
* *Notice: Modify the content in <>.
* *Notice: the passenger generation probabilities should be 0 at the end stop of each route. \n
* *Notice: the format of the configuration file can refer to config.txt which is the default configuration file for the program. \n
* 3. Start server by entering "./build/bin/config_sim <config_file_name>" in your terminal. Then you will see the simulation results printed on the terminal. \n
*
*/

/*! \page page2 Developer Guide
* \section subdes Structure of Domain Elements
* The project includes basic building blocks for a transit system including buses, passengers, stops and routes located in src directory
* They are corresponding to 4 classes.
* \subsection pas Passenger
* Passenger has attributes of his name, waiting time including that
* at stop and on bus and the id of his destination stop. Functions in this class can change the status of passenger.
*
* \subsection stop Stop
* Stop have its own id, list of passenger waiting at the stop, and its location information.
* Methods in this class enables to load passenger on bus when a bus arrives.
*
* \subsection bus Bus
* Each Bus object having 2 routes indicating an entire circulatory route. It also has a list of passengers on the bus, its speed
* and capacity. When stops try to load passenger on the bus, the bus will check if it is doable by checking if the bus is full.
* Buses move and update it's position based on the speed and distance to the next stop.
*
* \subsection route Route
* Route is constructed by a list of stops. It keeps track on next stops of the bus and provides it with distance information.
*
* \section subd Structure of Simulation Elements
* To simulate the transit system according to the realiistic situation, the project is also having components contributing to simulation. They are located in src directory.
* \subsection pf Passenger factory
* There are 2 versions of passenger factory. PassengerFactory is a class that generate randomized name for passengers while DPassengerFactory generate deterministic name that used for regression tests.
*
* \subsection pg Passenger generator
* There are 2 versions of passenger generators as well. RandomPassengerGenerator generate passengers at stops based on the probability of occurance at each stop.
* RtestPassengerGenerator however, generate the number of passengers at each stop based on the stop id. It is also used for regression test.
*
* \subsection cm configuration manager
* ConfigManager is a class that reads from users specified text file and generate busses, routes and stops based on the given information.
*
* \section sim Simulators
* Located in src directory.
* \subsection LocalSimulator
* It is basically imitating the transit system by creating instances of those classes and implement by logical process.
* \subsection rLocalSimulator
* It stortens the stops in eastbound and eastbound into 3 respectively, so the driver runs faster. Used for regression test.
* \subsection ConfigSimulator
* A simulator that runs the simulation given the specified busses, routes and stops.
*
* \section dri Drivers
* There are many drivers in the drivers directory of the project.
* \subsection Test Drivers
* Those are the drivers of the tests on domain elements and simulation elements of the project including busses, routes, passengers, stops, passenger factory and passenger generators.
* \subsection Regression Test Driver
* File named regression_driver is to drive the regression test.
* \subsection Transit Simulation Drivers
* There are 2 versions of simple transit simulation. The version in transit_sim.cc outputs the simulation process to the standard outstream while capture_transit_sim outputs the results to a specified file.
*/

#endif  // SRC_MAINPAGE_H_
