/*
 * Copyright (C) 2021 Changi General Hospital
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include "legacy_adapter_bridge_utils.hpp"

using namespace std::chrono_literals;

namespace legacy_adapter_bridge_utils
{
  LegacyAdapterBridgeUtils::load_parameters(const std::string& graph_file)
  {
    std::cout << "Loading graph file : " << graph_file << std::endl;
    const YAML::Node graph_config = YAML::LoadFile(graph_file);

    if(!graph_config)
    {
      std::cerr << "Failed to load graph file [" << graph_file << "]" << std::endl;
    }

    const YAML::Node levels = graph_config["levels"];
    if(!levels)
    {
      std::cerr << "Graph file [" << graph_file << "] is missing the [levels] key" << std::endl;
    }
    // Checks if there is a valid value(s) mapped to the key value(s)
    if(!levels.IsMap())
    {
      std::cerr << "The [levels] key does not point to a map in graph file [" << graph_file << "]" << std::endl;
    }

    for(const auto level : levels)
    {
      const std::string level_name_ = level.first.as<std::string>();
      std::cout << "Following waypoints below belong to" << level_name_ << std::endl;);

      const YAML::Node vertices = level.second["vertices"];
      std::vector<double> location;

      for(const auto vertex : vertices)
      {
        const YAML::Node& options = vertex[2];
        const YAML::Node& vertex_name = options["name"];
        if (vertex_name)
        {
          const std::string& name = vertex_name.as<std::string>();
          if (!name.empty())
          {
            location.push_back(vertex[0].as<double>());
            location.push_back(vertex[1].as<double>());
            std::pair<std::string, std::vector<double>> vertex_pair (name,location);
            rmf_nav_graph_data_.push_back(vertex_pair);
            location.clear();
          }
        } 
      }
    } 
    // [Optional] This is for sanity check in print out
    for (auto x : rmf_nav_graph_data_)
    {
      std::cout << "vertex name : ", x.first << std::endl;
      for (auto y: x.second)
      {
        std::cout << "coord : " << std::to_string(y) << std::endl;);
      }
    }
  }

  LegacyAdapterBridgeUtils::get_rmf_waypoint_name_from_location(rmf_fleet_msgs::msg::Location& _location)
  {
    if(!rmf_nav_graph_data_.size()) return "";
    double smallest_dist = std::numeric_limits<double>::max(); 
    std::string wp_name = "";
    
    for(auto element : rmf_nav_graph_data_) {
      auto delta = sqrt(pow((_location.x-element.second[0]),2) + pow((_location.y-element.second[1]),2));
      if(delta < smallest_dist && delta < ALLOWED_TRANSFORM_DELTA_){
        wp_name = element.first;
        smallest_dist = delta;
      }
    }
    return wp_name;
  }
}
