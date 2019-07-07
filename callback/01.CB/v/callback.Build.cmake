AMLEO Project
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(CALLBACK)
# Path to `motor` directory for OpenSceneGraph.
SET(MOTOR_DIR ${CMAKE_SOURCE_DIR}/../../../motor)

AMLEO Binary
SET(BINARY_NAME "callback-${STAGE_ID}")
# Create and link executable.
ADD_EXECUTABLE(${BINARY_NAME} callback.cpp)
# Use C++14.
TARGET_COMPILE_OPTIONS(${BINARY_NAME} PUBLIC "-std=c++14")
