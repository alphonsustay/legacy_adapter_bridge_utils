#ifndef LEGACY_ADAPTER_BRIDGE_UTILS_HPP
#define LEGACY_ADAPTER_BRIDGE_UTILS_HPP

#include <iostream>
#include <chrono>
#include <memory>
#include <yaml-cpp/yaml.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "rmf_fleet_msgs/msg/location.hpp"

namespace legacy_adapter_bridge_utils
{
  class LegacyAdapterBridgeUtils
  {
    private:
    std::vector<std::pair<std::string, std::vector<double>>> rmf_nav_graph_data_;
    double ALLOWED_TRANSFORM_DELTA_ = 0.2;

    public:

    void load_parameters(const std::string& graph_file);
    std::string get_rmf_waypoint_name_from_location(rmf_fleet_msgs::msg::Location& _location);
  }
}

#endif // LEGACY_ADAPTER_BRIDGE_UTILS_HPP