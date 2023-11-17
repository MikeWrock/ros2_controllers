cmake_minimum_required(VERSION 3.16)
project(pounce_command_controller LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(THIS_PACKAGE_INCLUDE_DEPENDS
  controller_interface
  generate_parameter_library
  hardware_interface
  pounce_msgs
  pluginlib
  rclcpp
  rclcpp_lifecycle
  realtime_tools
  std_msgs
)

find_package(ament_cmake REQUIRED)
find_package(backward_ros REQUIRED)
foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
  find_package(${Dependency} REQUIRED)
endforeach()

generate_parameter_library(
  pounce_command_controller_parameters
  src/pounce_command_controller_parameters.yaml
)

add_library(pounce_command_controller SHARED
  src/pounce_controllers_base.cpp
  src/pounce_command_controller.cpp
)
target_compile_features(pounce_command_controller PUBLIC cxx_std_17)
target_include_directories(pounce_command_controller PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/pounce_command_controller>
)
target_link_libraries(pounce_command_controller PUBLIC
  pounce_command_controller_parameters
)
ament_target_dependencies(pounce_command_controller PUBLIC ${THIS_PACKAGE_INCLUDE_DEPENDS})
# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(pounce_command_controller PRIVATE "POUNCE_COMMAND_CONTROLLER_BUILDING_DLL")
pluginlib_export_plugin_description_file(controller_interface pounce_command_plugin.xml)


install(
  DIRECTORY include/
  DESTINATION include/pounce_command_controller
)
install(
  TARGETS
    pounce_command_controller
    pounce_command_controller_parameters
  EXPORT export_pounce_command_controller
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  INCLUDES DESTINATION include
)

ament_export_targets(export_pounce_command_controller HAS_LIBRARY_TARGET)
ament_export_dependencies(${THIS_PACKAGE_INCLUDE_DEPENDS})
ament_package()
