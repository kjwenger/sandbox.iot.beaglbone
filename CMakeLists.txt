cmake_minimum_required(VERSION 2.6)
project(sandbox-iot-beaglebone)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Debug-armhf" CACHE STRING "" FORCE)

add_subdirectory(test)

add_subdirectory(sample)
