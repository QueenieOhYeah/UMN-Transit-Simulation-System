/**
* @file passenger_UT.cc
*
* @copyright 2019 Ziqian Qiu, All rights reserved.
*/

/* STUDENTS: YOU MUST ADD YOUR PASSENGER UNIT TESTS TO THIS FILE. FORMAT YOUR
 * TESTS TO FIT THE SPECIFICATIONS GIVEN BY THE TESTS PROVIDED IN THIS FILE.
 *
 * Please note, the assessment tests for grading, will use the same include
 * files, class names, and function names for accessing students' code that you
 * find in this file.  So students, if you write your code so that it passes
 * these feedback tests, you can be assured that the auto-grader will at least
 * be able to properly link with your code.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "../src/passenger.h"
/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class PassengerTests : public ::testing::Test {
 protected:
    Passenger* passenger;

  virtual void SetUp() {
    passenger = new Passenger();
    }

  virtual void TearDown() {
    delete passenger;
    }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(PassengerTests, Constructor) {
    EXPECT_EQ(passenger->IsOnBus(), false);
    passenger->GetOnBus();
    EXPECT_EQ(passenger->IsOnBus(), true);
}


TEST_F(PassengerTests, Destination) {
    EXPECT_EQ(passenger->GetDestination(), -1);
    Passenger* passenger2 = new Passenger(3, "A");
    EXPECT_EQ(passenger2->GetDestination(), 3);
}

TEST_F(PassengerTests, Update) {
    passenger->Update();
    EXPECT_NE(passenger->GetTotalWait(), 2);
    passenger->Update();
    EXPECT_EQ(passenger->GetTotalWait(), 2);
}


TEST_F(PassengerTests, Onbus) {
    passenger->GetOnBus();
    passenger->Update();
    EXPECT_EQ(passenger->GetTotalWait(), 1);
}

TEST_F(PassengerTests, Report) {
    testing::internal::CaptureStdout();
    passenger->Report(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    std::string result =
    "Name: Nobody\nDestination: -1\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
    EXPECT_EQ(output, result);
}
