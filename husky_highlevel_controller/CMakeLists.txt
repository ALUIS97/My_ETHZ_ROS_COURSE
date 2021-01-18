cmake_minimum_required(VERSION 2.8.3)
project(husky_highlevel_controller)

## Use C++11
add_definitions(--std=c++11)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS
    include
#  LIBRARIES
  CATKIN_DEPENDS 
    roscpp
    sensor_msgs
    geometry_msgs
    visualization_msgs	
#  DEPENDS 
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(${PROJECT_NAME}
  src/${PROJECT_NAME}_node.cpp
  src/HuskyHighlevelController.cpp
)

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)


add_executable(scan_listen src/scan_listen.cpp)
add_dependencies(scan_listen ${${PROJECT_NAME}_EXPORTED_TRAGETS}
${catkin_EXPORTED_TARGETS})
target_link_libraries(scan_listen ${catkin_LIBRARIES})



add_executable(scan_param PARAMETERES/scan_param.cpp)
add_dependencies(scan_param ${${PROJECT_NAME}_EXPORTED_TRAGETS}
${catkin_EXPORTED_TARGETS})
target_link_libraries(scan_param ${catkin_LIBRARIES})


add_executable(pub_sub_pillar src/pub_sub_pillar.cpp)
add_dependencies(pub_sub_pillar ${${PROJECT_NAME}_EXPORTED_TRAGETS}
${catkin_EXPORTED_TARGETS})
target_link_libraries(pub_sub_pillar ${catkin_LIBRARIES})


add_executable(mark_scan src/mark_scan.cpp)
add_dependencies(mark_scan ${${PROJECT_NAME}_EXPORTED_TRAGETS}
${catkin_EXPORTED_TARGETS})
target_link_libraries(mark_scan ${catkin_LIBRARIES})




