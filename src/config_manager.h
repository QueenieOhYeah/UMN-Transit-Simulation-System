/**
 * @file bus.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_CONFIG_MANAGER_H_
#define SRC_CONFIG_MANAGER_H_

#include <vector>
#include <string>


class Route;
/**
 * @brief The main class to read from configuration files
 *
 */
class ConfigManager {
 public:
        ConfigManager();
        ~ConfigManager();

        /**
         * @brief Method read from configuration file
         *
         *
         *
         * @return a Boolean value indicating if read successfully, if so return 1 else return 0
         */
        int ReadConfig(const std::string filename);
        /**
         * @brief Getter of route derived from configuration file
         *
         * @return vector<Route *>
         */
        std::vector<Route *> GetRoutes() const { return routes; }
 private:
        std::vector<Route *> routes;
};

#endif  // SRC_CONFIG_MANAGER_H_
