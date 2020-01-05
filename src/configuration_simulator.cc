/**
 * @file configuration_simulator.cc
 *
 * @copyright 2019 Ziqian Qiu, All rights reserved.
 */
#include "src/configuration_simulator.h"

#include "src/bus.h"
#include "src/route.h"

/**
* @brief Constructs a ConfigSimulator
*
* @param[in] ConfigManager
*
*/
ConfigSimulator::ConfigSimulator(ConfigManager* configM) {
    configManager_ = configM;
}

ConfigSimulator::~ConfigSimulator() {
}

void ConfigSimulator::Start(const std::vector<int>& busStartTimings) {
    busStartTimings_ = busStartTimings;

    timeSinceLastBus_.resize(busStartTimings_.size());
    for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
        timeSinceLastBus_[i] = 0;
    }

    simulationTimeElapsed_ = 0;

    prototypeRoutes_ = configManager_->GetRoutes();
    for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
        prototypeRoutes_[i]->Report(std::cout);

        prototypeRoutes_[i]->UpdateRouteData();
    }
}

void ConfigSimulator::Update() {
    simulationTimeElapsed_++;

    std::cout << "~~~~~~~~~~ The time is now " << simulationTimeElapsed_;
    std::cout << "~~~~~~~~~~" << std::endl;

    std::cout << "~~~~~~~~~~ Generating new busses if needed ";
    std::cout << "~~~~~~~~~~" << std::endl;

    // Check if we need to generate new busses
    for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
        // Check if we need to make a new bus
        if (0 >= timeSinceLastBus_[i]) {
            Route * outbound = prototypeRoutes_[0];
            Route * inbound = prototypeRoutes_[1];

            busses_.push_back(new Bus(std::to_string(busId), outbound->Clone(),
                                      inbound->Clone(), 60, 1));
            busId++;

            timeSinceLastBus_[i] = busStartTimings_[i];
        } else {
            timeSinceLastBus_[i]--;
        }
    }

    std::cout << "~~~~~~~~~ Updating routes ";
    std::cout << "~~~~~~~~~" << std::endl;
    // Update routes
    for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
        prototypeRoutes_[i]->Update();

        prototypeRoutes_[i]->Report(std::cout);
    }


    std::cout << "~~~~~~~~~ Updating busses ";
    std::cout << "~~~~~~~~~" << std::endl;

    // Update busses
    for (int i = static_cast<int>(busses_.size()) - 1; i >= 0; i--) {
        busses_[i]->Update();

        if (busses_[i]->IsTripComplete()) {
            busses_.erase(busses_.begin() + i);
            continue;
        }
        busses_[i]->Report(std::cout);
    }
}
