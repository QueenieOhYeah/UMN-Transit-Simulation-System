# UMN Transit Simulation System

## Download
Download the project at my github repository

## Steps to run the Simulators
#### Compile the program
1. Open the terminal in your own machine, direct to the project directory. Type "make" to compile the program.

#### Run the Visualization Simulation
**NOTE**: The visualization simulation relies on files in Lab machines, therefore connection to Lab mechines in the University of Minnesota is required to run the visualization simulation.

Step by step for CSE Labs or vole users
1. Navigate to base project directory(project/) 
2. Start server by entering `./build/bin/vis_sim <port_number>` in your terminal. 
**NOTE**:  <port_number> can be anything. Try and pick numbers above 8000 and not multiples of 10.
**NOTE**: You must run by doing `./build/bin/vis_sim <port_number>`. You cannot cd to bin/ and run ./vis_sim <port_number>. \n
3. Navigate to the following address on your VOLE browser (Firefox/Chrome): 
`http://127.0.0.1:<port_number>/web_graphics/project.html`

Step by step for ssh users
You can SSH using a Windows machine with Git Bash: ssh -L <port number>:127.0.0.1:<port_number> <x500>@<cse_labs_computer>.cselabs.umn.edu
1. Navigate to base project directory(project/) 
2. Start server by entering "./build/bin/vis_sim <port_number>" in your terminal. 
**NOTE**:  <port_number> can be anything. Try and pick numbers above 8000 and not multiples of 10.
**NOTE**:  You must run by doing `./build/bin/vis_sim <port_number>`. You cannot cd to bin/ and run `./vis_sim <port_number>`. 
3. Navigate to the following address on your LOCAL machine using your LOCAL browser (Firefox/Chrome): 
`http://127.0.0.1:<port_number>/web_graphics/project.html`

#### Run the Configuration Simulation
The program provides a simulator that enables the users to specified the features of the domain elements in the program involving busses, routes and stops. Since it is not using visualized graphics, it is not necessary to connect to the Lab machine in the University of Minnesota.

##### Run the default congifuration simulation
1. Navigate to base project directory(project/) 
2. Start server by entering "./build/bin/config_sim" in your terminal. Then you will see the simulation results printed on the terminal. 

##### Add your own configuration and run the simulator
1. Navigate to project/config directory
2. Create your own configuration file and save in the directory as .txt 

Format of the configuration file: 
ROUTE_GENERAL, <Bus_name> 
ROUTE, <Route_named> 
STOP, <stop_name>, <stop_longitute>, <stop_latitute>, <passenger_generation_probabilities> 
(Multiple stops) 
.
.
.
ROUTE, <route_name> 
STOP, <stop_name>, <stop_longitute>, <stop_latitute>, <passenger_generation_probabilities> \n
(Multiple stops) 
.
.
.
**NOTE**: Modify the content in <>.
**NOTE**: the passenger generation probabilities should be 0 at the end stop of each route. 
**NOTE**: the format of the configuration file can refer to config.txt which is the default configuration file for the program. 

3. Start server by entering "./build/bin/config_sim <config_file_name>" in your terminal. Then you will see the simulation results printed on the terminal.
