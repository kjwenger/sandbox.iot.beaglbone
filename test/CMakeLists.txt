cmake_minimum_required(VERSION 2.6)
project(sandbox-iot-beaglebone)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Debug-armhf" CACHE STRING "" FORCE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if (NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/usr)
endif (NOT DEFINED CMAKE_PREFIX_PATH)

file(GLOB INCLUDE
        ../include/*.hpp
)
file(GLOB SRC_SHARED
        ../src/*.cpp
)

include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_PREFIX_PATH}/local/include
        ${CMAKE_PREFIX_PATH}/include
        /usr/local/include
        /usr/include/modbus
        /usr/include
)

add_subdirectory(thirdparty)

enable_testing()

file(GLOB TEST_INCLUDE
        include/*.hpp
)
file(GLOB TEST_SRC
        src/*.cpp
)

#find_package(Modbus)

add_executable(sandbox-iot-beaglebone-test
        ${TEST_INCLUDE}
        ${SRC_SHARED}
        ${TEST_SRC}
)
target_include_directories(sandbox-iot-beaglebone-test PUBLIC
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
        ${CMAKE_PREFIX_PATH}/local/include
        ${CMAKE_PREFIX_PATH}/include
        include
)
target_link_libraries(sandbox-iot-beaglebone-test
#        ${MODBUS_LIBRARY}
        modbus
        gtest_main
        gtest)

add_test(
        NAME sandbox-iot-beaglebone-test
        COMMAND sandbox-iot-beaglebone-test
)
