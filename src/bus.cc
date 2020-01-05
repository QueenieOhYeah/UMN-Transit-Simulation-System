/**
 * @file bus.cc
 *
 * @copyright 2019 Ziqian Qiu, All rights reserved.
 */
#include "src/bus.h"

Bus::Bus(std::string name, Route * out, Route * in,
  int capacity, double speed) {
  name_ = name;
  outgoing_route_ = out;
  incoming_route_ = in;
  passenger_max_capacity_ = capacity;
  speed_ = speed;
  distance_remaining_ = 1;
}

bool Bus::LoadPassenger(Passenger * new_passenger) {
  if (static_cast<int>(passengers_.size()) == passenger_max_capacity_) {
    return false;
  }
  if (!new_passenger->IsOnBus()) {
    new_passenger->GetOnBus();
    passengers_.push_back(new_passenger);
    return true;
  }
  return false;
}

// Pass in the pointer to the destination stop in this function when arrives
int Bus::UnloadPassengers(Stop * stop) {
  int count = 0;
  for (std::list<Passenger *>::const_iterator it = passengers_.begin();
  it != passengers_.end(); it++) {
    if ((*it)->GetDestination() == stop->GetId()) {
      passengers_.erase(it);
      it--;
      count++;
    }
  }
  return count;
}

bool Bus::IsTripComplete() {
  return (incoming_route_->IsAtEnd() && outgoing_route_->IsAtEnd());
}

bool Bus::Move() {
  if (distance_remaining_ <= 0) return false;
  distance_remaining_ -= speed_;
  return true;
}

// bool Refuel() {
//  //This may become more complex in the future
//  fuel_ = max_fuel_;
// }

void Bus::Update() {  // using common Update format
  Move();
  // Distance_remaining_ is non-positive, bus stops
  if (distance_remaining_ <= 0) {
    if (outgoing_route_->IsAtEnd()) {  // Outgoing_route_ reaches to end
      if (!incoming_route_->IsAtEnd()) {
        // Get pointer to destination stop
        Stop * stop_arrived_at = incoming_route_->GetDestinationStop();
        UnloadPassengers(stop_arrived_at);
        stop_arrived_at->LoadPassengers(this);
        distance_remaining_ = incoming_route_->GetNextStopDistance();
        incoming_route_->NextStop();  // Change pointer to next stop
      }
    } else {  // Outgoing_route_ hasn't reached to end
      Stop * stop_arrived_at = outgoing_route_->GetDestinationStop();
      UnloadPassengers(stop_arrived_at);
      stop_arrived_at->LoadPassengers(this);
      distance_remaining_ = outgoing_route_->GetNextStopDistance();
      outgoing_route_->NextStop();
    }
  }
  for (std::list<Passenger *>::iterator it = passengers_.begin();
  it != passengers_.end(); it++) {
    (*it)->Update();
  }
  UpdateBusData();
}

void Bus::Report(std::ostream &out) {
  out << "Name: " << name_ << std::endl;
  out << "Speed: " << speed_ << std::endl;
  out << "Distance to next stop: " << distance_remaining_ << std::endl;
  out << "\tPassengers (" << passengers_.size() << "): " << std::endl;
  for (std::list<Passenger *>::iterator it = passengers_.begin();
  it != passengers_.end(); it++) {
    (*it)->Report(out);
  }
}

void Bus::UpdateBusData() {
  bus_data_.id = GetName();
  Position pos;
  Stop * next_stop = GetNextStop();
  Stop * previous_stop = GetPreviousStop();
  pos.x = (next_stop->GetLong() + previous_stop->GetLong())/2;
  pos.y = (next_stop->GetLat() + previous_stop->GetLat())/2;
  bus_data_.position = pos;
  bus_data_.num_passengers = static_cast<int>(GetNumPassengers());
  bus_data_.capacity = GetCapacity();
}

BusData Bus::GetBusData() {
  return bus_data_;
}

std::string Bus::GetName() const {
  return name_;
}

Stop * Bus::GetNextStop() {
  if (distance_remaining_ <= 0) {
    std::cout << "here" << std::endl;
    return GetPreviousStop();
  }
  if (!outgoing_route_->IsAtEnd()) return outgoing_route_->GetNextStop();
  return incoming_route_->GetNextStop();
}

Stop * Bus::GetPreviousStop() {
  if (!outgoing_route_->IsAtEnd()) {
      return outgoing_route_->GetPreviousStop();
  } else {
      return incoming_route_->GetPreviousStop();
  }
}

size_t Bus::GetNumPassengers() {
  return passengers_.size();
}
int Bus::GetCapacity() {
  return passenger_max_capacity_;
}
