#include <gtest/gtest.h>
#include "../src/bus.h"
#include "../src/route.h"
#include "../src/stop.h"
#include "../src/passenger.h"
#include "../src/data_structs.h"
#include "../src/random_passenger_generator.h"
#include <iostream>

class BusTests : public ::testing::Test {
 protected:
    Stop ** in_stops = new Stop *[2];
    Stop ** out_stops = new Stop *[2];
    std::list<Stop *> in_stops_list;
    std::list<Stop *> out_stops_list;
    double * in_distances;
    double * out_distances;
    std::list<double> in_probs;
    std::list<double> out_probs;
    Bus * bus;
    Route * OUT;
    Route * IN;
    RandomPassengerGenerator * in_generator;
    RandomPassengerGenerator * out_generator;
    Stop* stop_1 = new Stop(0, 10, 10);
    Stop* stop_2 = new Stop(1, 20, 20);
    Stop* stop_3 = new Stop(2, 20, 20);
    Stop* stop_4 = new Stop(3, 10, 10);


  virtual void SetUp() {
    in_stops_list.push_back(stop_2);
    in_stops[0] = stop_2;
    in_stops_list.push_back(stop_1);
    in_stops[1] = stop_1;

    out_stops_list.push_back(stop_1);
    out_stops[0] = stop_1;
    out_stops_list.push_back(stop_2);
    out_stops[1] = stop_2;

    in_distances = new double[1];
    out_distances = new double[1];
    in_distances[0] = 2;
    out_distances[0] = 2;

    //std::list<double> in_probs;
    in_probs.push_back(.15);
    in_probs.push_back(0);
    //std::list<double> out_probs;  //realistic .15, .3, .025, .05, .05, 0
    out_probs.push_back(.3); //WB
    out_probs.push_back(0);
    in_generator = new RandomPassengerGenerator(in_probs, in_stops_list);
    out_generator = new RandomPassengerGenerator(out_probs, out_stops_list);
    OUT = new Route("Out", out_stops, out_distances, 2, out_generator);
    IN = new Route("In", in_stops, in_distances, 2, in_generator);
    bus = new Bus("1", OUT, IN, 2, 1);
    }

  virtual void TearDown() {
    delete bus;
    delete in_stops;
    delete out_stops;
    delete in_distances;
    delete out_distances;
    delete OUT;
    delete IN;
    delete stop_1;
    delete stop_2;
    delete stop_3;
    delete stop_4;
    }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(BusTests, Constructor) {
    EXPECT_EQ(bus->GetName(), "1");
    EXPECT_EQ(bus->GetCapacity(), 2);
}


TEST_F(BusTests, LoadAndUnload) {
    Passenger* p = new Passenger(0,"A");
    Passenger* p2 = new Passenger(0,"B");
    Passenger* p3 = new Passenger(0,"C");
    EXPECT_EQ(bus->LoadPassenger(p), true);
    EXPECT_EQ(bus->GetNumPassengers(), 1);
    // Reload a same passenger already on bus
    EXPECT_NE(bus->LoadPassenger(p), true);
    EXPECT_EQ(bus->LoadPassenger(p2), true);
    // Capacity reached
    EXPECT_EQ(bus->LoadPassenger(p3), false);
    // Unload not at destination stop
    EXPECT_EQ(bus->UnloadPassengers(stop_2), 0);
    // Unload passengers at destination stop
    EXPECT_EQ(bus->UnloadPassengers(stop_1), 2);
    // No passenger on bus
    EXPECT_EQ(bus->UnloadPassengers(stop_1), 0);

}

TEST_F(BusTests, Stops) {
    EXPECT_EQ(bus->IsTripComplete(),false);
    EXPECT_EQ(bus->GetNextStop(), stop_1);
    EXPECT_EQ(bus->GetPreviousStop(),stop_1);
    bus->Update();
    EXPECT_EQ(bus->GetNextStop(), stop_2);
    EXPECT_EQ(bus->GetPreviousStop(),stop_1);
    bus->Update();
    // Distance between two stops is 2
    EXPECT_EQ(bus->GetNextStop(), stop_2);
    EXPECT_EQ(bus->GetPreviousStop(),stop_1);
    bus->Update();
    EXPECT_EQ(bus->GetNextStop(), stop_2);
    EXPECT_EQ(bus->GetPreviousStop(),stop_2);
    bus->Update();
    EXPECT_EQ(bus->GetNextStop(), stop_1);
    EXPECT_EQ(bus->GetPreviousStop(),stop_2);
    bus->Update();
    EXPECT_EQ(bus->GetNextStop(), stop_1);
    EXPECT_EQ(bus->GetPreviousStop(),stop_2);
    bus->Update();
    EXPECT_EQ(bus->IsTripComplete(),true);
}

TEST_F(BusTests, Report) {
    testing::internal::CaptureStdout();
    bus->Report(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    std::string result =
    "Name: 1\nSpeed: 1\nDistance to next stop: 1\n\tPassengers (0): \n";
    EXPECT_EQ(output, result);
}

TEST_F(BusTests, BusData) {
    // Initialzed BusData
    EXPECT_EQ(bus->GetBusData().id, "");
    EXPECT_EQ(bus->GetBusData().position.x, 0);
    EXPECT_EQ(bus->GetBusData().position.y, 0);
    EXPECT_EQ(bus->GetBusData().capacity, 0);
    EXPECT_EQ(bus->GetBusData().num_passengers, 0);
    bus->UpdateBusData();
    EXPECT_EQ(bus->GetBusData().id, "1");
    EXPECT_EQ(bus->GetBusData().position.x, 10);
    EXPECT_EQ(bus->GetBusData().position.y, 10);
    EXPECT_EQ(bus->GetBusData().capacity, 2);
    EXPECT_EQ(bus->GetBusData().num_passengers, 0);
}
