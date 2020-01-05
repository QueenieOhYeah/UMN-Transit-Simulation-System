/**
 * @file route.cc
 *
 * @copyright 2019 Ziqian Qiu, All rights reserved.
 */
#include "src/route.h"
#include "src/data_structs.h"
Route::Route(std::string name, Stop ** stops, double * distances,
  int num_stops, PassengerGenerator* pg) {
  for (int i = 0; i < num_stops; i++) {
    stops_.push_back(stops[i]);
  }
  for (int i = 0; i < num_stops - 1; i++) {
    distances_between_.push_back(distances[i]);
  }

  name_ = name;
  num_stops_ = num_stops;
  generator_ = pg;
  std::list<Stop *>::iterator it = stops_.begin();
  destination_stop_ = (*it);
  previous_stop_ = (*it);
  destination_stop_index_ = 0;
}

// Copy and convert the data structure and store in heap
// Create new Route with them
Route * Route::Clone() {
  double * distances = new double[num_stops_ - 1];
  Stop ** stops = new Stop *[num_stops_];
  int count = 0;
  for (std::list<Stop *>::const_iterator it = stops_.begin();
  it != stops_.end(); it++) {
    stops[count] = (*it);
    count++;
    if (count == num_stops_) count = 0;
  }
  for (std::list<double>::const_iterator it = distances_between_.begin();
  it != distances_between_.end(); it++) {
    distances[count] = (*it);
    count++;
  }
  return new Route(name_, stops, distances, num_stops_, generator_);
}

bool Route::IsAtEnd() const {
  return (destination_stop_index_ >= num_stops_);
}

void Route::NextStop() {
  if (destination_stop_index_ < num_stops_) {
    std::list<Stop *>::iterator it = stops_.begin();
    std::advance(it, destination_stop_index_);
    destination_stop_ = (*it);
  }
}

Stop * Route::GetNextStop() {
  return destination_stop_;
}

Stop * Route::GetPreviousStop() {
    std::list<Stop *>::iterator it = stops_.begin();
    if (destination_stop_index_ >= 1) {
      std::advance(it, destination_stop_index_ - 1);
      previous_stop_ = (*it);
    }
    return previous_stop_;
}


double Route::GetNextStopDistance() {
  if (destination_stop_index_ < num_stops_ - 1) {
    std::list<double>::iterator it = distances_between_.begin();
    std::advance(it, destination_stop_index_);
    destination_stop_index_++;
    return (*it);
  }
  destination_stop_index_++;
  return -1;
}

Stop * Route::GetDestinationStop() const {
  return destination_stop_;
}

void Route::Update() {
  GenerateNewPassengers();
  UpdateRouteData();
  for (std::list<Stop *>::iterator it = stops_.begin();
  it != stops_.end(); it++) {
    (*it)->Update();
  }
}

int Route::GenerateNewPassengers() {
  int num = generator_->GeneratePassengers();
  return num;
}

std::string Route::GetName() {
  return name_;
}

std::list<Stop *> Route::GetStops() {
  return stops_;
}

void Route::UpdateRouteData() {
  route_data_.id = GetName();
  route_data_.stops.clear();
  std::vector<StopData> stops_v;
  StopData stop_data_;
  Position pos;
  for (std::list<Stop *>::iterator it = stops_.begin();
  it != stops_.end(); it++) {
    stop_data_.id = (*it)->GetName();
    pos.x = (*it)->GetLong();
    pos.y = (*it)->GetLat();
    stop_data_.position = pos;
    stop_data_.num_people = static_cast<int>((*it)->GetNumPassengers());
    stops_v.push_back(stop_data_);
  }
  route_data_.stops = stops_v;
}

RouteData Route::GetRouteData() {
  return route_data_;
}

void Route::Report(std::ostream &out) {
  out << "Name: " << name_ << std::endl;
  out << "Num stops: " << num_stops_ << std::endl;
  // Test
  // out << stops_.size() << std::endl;
  int stop_counter = 0;
  for (std::list<Stop *>::const_iterator it = stops_.begin();
  it != stops_.end(); it++) {
    (*it)->Report(out);
    stop_counter++;
  }
}
