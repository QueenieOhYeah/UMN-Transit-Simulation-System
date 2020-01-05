#include <gtest/gtest.h>
#include "../src/stop.h"
#include "../src/passenger.h"
#include <iostream>

class StopTests : public ::testing::Test {
 protected:
    Stop* stop;

  virtual void SetUp() {
    stop = new Stop(0, 10, 20);
    }

  virtual void TearDown() {
    delete stop;
    }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(StopTests, Constructor) {
    EXPECT_EQ(stop->GetId(), 0);
    EXPECT_EQ(stop->GetLong(), 10);
    EXPECT_EQ(stop->GetLat(), 20);
}

TEST_F(StopTests, passenger) {
    Passenger* p = new Passenger();
    EXPECT_EQ(stop->GetNumPassengers(), 0);
    EXPECT_EQ(stop->AddPassengers(p), 1);
    EXPECT_EQ(stop->GetNumPassengers(), 1);
}

TEST_F(StopTests, Report) {
    Passenger* p = new Passenger();
    stop->AddPassengers(p);
    stop->Update();
    testing::internal::CaptureStdout();
    stop->Report(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    std::string result =
    "ID: 0\nPassengers waiting: 1\nName: Nobody\nDestination: -1\nTotal Wait: 1\n\tWait at Stop: 1\n\tTime on bus: 0\n";
    EXPECT_EQ(output, result);
}
