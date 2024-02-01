rm -rf /home/orangepi/catkin_ws/src/clbrobot_project/clbrobot/maps/house.pgm 
rm -rf /home/orangepi/catkin_ws/src/clbrobot_project/clbrobot/maps/house.yaml

rosservice call /write_state /home/orangepi/catkin_ws/src/clbrobot_project/clbrobot/maps/map.bag.pbstream

rosrun cartographer_ros cartographer_pbstream_to_ros_map -pbstream_filename=/home/orangepi/catkin_ws/src/clbrobot_project/clbrobot/maps/map.bag.pbstream


cp  /home/orangepi/catkin_ws/src/clbrobot_project/clbrobot/maps/map.pgm /home/orangepi/catkin_ws/src/clbrobot_project/clbrobot/maps/house.pgm

cp  /home/orangepi/catkin_ws/src/clbrobot_project/clbrobot/maps/map.yaml /home/orangepi/catkin_ws/src/clbrobot_project/clbrobot/maps/house.yaml

