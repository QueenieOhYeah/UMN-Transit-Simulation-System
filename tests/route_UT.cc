#include <gtest/gtest.h>
#include "../src/route.h"
#include "../src/stop.h"
#include "../src/passenger.h"
#include "../src/data_structs.h"
#include "../src/random_passenger_generator.h"
#include <iostream>

class RouteTests : public ::testing::Test {
 protected:
    Stop ** stops = new Stop *[2];
    std::list<Stop *> stops_list;
    double * distances;
    std::list<double> probs;
    Route * route;
    RandomPassengerGenerator * generator;
    Stop* stop_1 = new Stop(0, 10, 10);
    Stop* stop_2 = new Stop(1, 20, 20);



  virtual void SetUp() {
    stops_list.push_back(stop_1);
    stops[0] = stop_1;
    stops_list.push_back(stop_2);
    stops[1] = stop_2;
    distances = new double[1];
    distances[0] = 2;
    probs.push_back(.3);
    probs.push_back(0);
    generator = new RandomPassengerGenerator(probs, stops_list);
    route = new Route("100", stops, distances, 2, generator);
    }

  virtual void TearDown() {
    delete stops;
    delete distances;
    delete route;
    delete stop_1;
    delete stop_2;
    }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(RouteTests, Constructor) {
    EXPECT_EQ(route->GetName(), "100");
    EXPECT_EQ(route->GetStops().size(), 2);
    Route* route2 = route->Clone();
    route->UpdateRouteData();
    route2->UpdateRouteData();
    EXPECT_EQ(route->GetName(), route2->GetName());
    EXPECT_EQ(route->GetStops(), route2->GetStops());
    route->UpdateRouteData();
    route2->UpdateRouteData();
    EXPECT_EQ(route->GetRouteData().id, route2->GetRouteData().id);
    EXPECT_EQ(route->GetRouteData().stops[0].id, route2->GetRouteData().stops[0].id);
    EXPECT_EQ(route->GetRouteData().stops[0].position.x, route2->GetRouteData().stops[0].position.x);
    EXPECT_EQ(route->GetRouteData().stops[0].position.y, route2->GetRouteData().stops[0].position.y);
    EXPECT_EQ(route->GetRouteData().stops[0].num_people, route2->GetRouteData().stops[0].num_people);
    EXPECT_EQ(route->GetRouteData().stops[1].id, route2->GetRouteData().stops[1].id);
    EXPECT_EQ(route->GetRouteData().stops[1].position.x, route2->GetRouteData().stops[1].position.x);
    EXPECT_EQ(route->GetRouteData().stops[1].position.y, route2->GetRouteData().stops[1].position.y);
    EXPECT_EQ(route->GetRouteData().stops[1].num_people, route2->GetRouteData().stops[1].num_people);
}

TEST_F(RouteTests, Stops) {
    EXPECT_EQ(route->IsAtEnd(),false);
    EXPECT_EQ(route->GetDestinationStop(), stop_1);
    EXPECT_EQ(route->GetPreviousStop(), stop_1);
    EXPECT_EQ(route->GetNextStopDistance(),2);
    route->NextStop();
    EXPECT_EQ(route->GetDestinationStop(), stop_2);
    EXPECT_EQ(route->GetPreviousStop(), stop_1);
    EXPECT_LT(route->GetNextStopDistance(),0);
    EXPECT_EQ(route->IsAtEnd(),true);
    EXPECT_EQ(route->GetNextStopDistance(),-1);
    route->GetNextStopDistance();
    route->GetNextStopDistance();
    EXPECT_EQ(route->IsAtEnd(),true);
}

TEST_F(RouteTests, Report) {
    testing::internal::CaptureStdout();
    route->Report(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    std::string result =
    "Name: 100\nNum stops: 2\nID: 0\nPassengers waiting: 0\nID: 1\nPassengers waiting: 0\n";
    EXPECT_EQ(output, result);
}

TEST_F(RouteTests, RouteData) {
    route->UpdateRouteData();
    EXPECT_EQ(route->GetRouteData().id, "100");
    EXPECT_EQ(route->GetRouteData().stops[0].id, "0");
    EXPECT_EQ(route->GetRouteData().stops[0].position.x, 10);
    EXPECT_EQ(route->GetRouteData().stops[0].position.y, 10);
    EXPECT_EQ(route->GetRouteData().stops[0].num_people, 0);
    EXPECT_EQ(route->GetRouteData().stops[1].id, "1");
    EXPECT_EQ(route->GetRouteData().stops[1].position.x, 20);
    EXPECT_EQ(route->GetRouteData().stops[1].position.y, 20);
    EXPECT_EQ(route->GetRouteData().stops[1].num_people, 0);
}
