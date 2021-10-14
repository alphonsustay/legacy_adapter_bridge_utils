# legacy_adapter_bridge_utils
This is a temporary repo for bridging legacy Traffic Light API Fleets to the current [RMF](https://github.com/open-rmf/rmf_ros2). **Note that users are still required to work on converting their adapters to the latest APIs**

## Background
To support existing implementers still running legacy Traffic Light API Fleet Adapters, this repository will provide the required functions to enable the fleets to continue interacting with RMF. However, these adapters will now be considered low compliance as they will be running as the current read-only fleets.

## Usage
There are current 2 available functions in the LegacyAdapterBridgeUtil Class

1. `load_parameter` : The function will expect to be given the directory location of the relevant navgraph yaml file. It will then store all waypoints found in the navgraph as an array.

2. `get_rmf_waypoint_name_from_location` : The function will expect to be given location information in the form of `rmf_fleet_msgs/msg/location`, and return the respective waypoint name based on the data obtained from the navgraph provided. In the event that there is no relevant waypoint, the function will return an empty string. **In ideal cases, the location coordinates given, should match the respective RMF waypoint coordinates exactly. However, in the function, an deviation delta (`ALLOWED_TRANSFORM_DELTA_`) has been accounted for and this value can be changed by the user. The default value is 0.2 metres.

## Additional Information for relevant users

As mentioned above, for users using the old version of the Traffic Light APIs, this repo will help one continue to interact with RMF as a read-only fleet, which is the lowest level of compliance with RMF. The 'Stop/Resume' feature in the Traffic Light Fleet will be lost as RMF will not have control over the Fleet. 

As a read-only fleet, in order for RMF to know what your planned destination is, users are required to add the waypoint name as defined in [Traffic Editor](https://github.com/open-rmf/rmf_traffic_editor). The names of the waypoints can be obtained from the navgraph which can be done through the `get_rmf_waypoint_name_from_location` function mentioned above.
