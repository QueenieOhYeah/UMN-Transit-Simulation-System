/**
 * @file stop.cc
 *
 * @copyright 2019 Ziqian Qiu, All rights reserved.
 */
#include <iostream>
#include <vector>
#include <string>

#include "src/stop.h"

Stop::Stop(int id, double longitude, double latitude) :
id_(id), longitude_(longitude), latitude_(latitude) {
  // Defaults to Westbound Coffman Union stop
  // no initialization of list of passengers necessary
}

int Stop::AddPassengers(Passenger * pass) {
  passengers_.push_back(pass);
  return 1;
}

int Stop::LoadPassengers(Bus * bus) {
  // loading some passengers onto a bus
  int count = 0;
  for (std::list<Passenger *>::const_iterator it = passengers_.begin();
  it != passengers_.end(); it++) {
    if (bus -> LoadPassenger(*it)) {
      passengers_.erase(it);
      it--;
      count++;
    }
  }
  return count;
}

void Stop::Update() {
  for (std::list<Passenger *>::iterator it = passengers_.begin();
  it != passengers_.end(); it++) {
    (*it)->Update();
  }
}

int Stop::GetId() const {
  return id_;
}

double Stop::GetLong() {
  return longitude_;
}

double Stop::GetLat() {
  return latitude_;
}

std::string Stop::GetName() {
  return std::to_string(id_);
}

size_t Stop::GetNumPassengers() {
  return passengers_.size();
}

void Stop::Report(std::ostream &out) const {
  out << "ID: " << id_ << std::endl;
  out << "Passengers waiting: " << passengers_.size() << std::endl;
  for (std::list<Passenger *>::const_iterator it = passengers_.begin();
  it != passengers_.end(); it++) {
    (*it)->Report(out);
  }
}
