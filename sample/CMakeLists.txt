cmake_minimum_required(VERSION 2.6)
project(sandbox-iot-beaglebone)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Debug-armhf" CACHE STRING "" FORCE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if (NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/usr)
endif (NOT DEFINED CMAKE_PREFIX_PATH)

if(CMAKE_COMPILER_IS_GNUCC)
    message(STATUS "=== GCC C COMPILER DETECTED")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb -D_DEBUG -O0")
endif(CMAKE_COMPILER_IS_GNUCC)

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach(_variableName ${_variableNames})

include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_PREFIX_PATH}/local/include
        ${CMAKE_PREFIX_PATH}/include
        /usr/local/include
        /usr/include/modbus
        /usr/include
)

#find_package(Modbus)

add_executable(modbus-master
        src/modbus-master.c
)
target_include_directories(modbus-master PUBLIC
        ${CMAKE_PREFIX_PATH}/local/include
        ${CMAKE_PREFIX_PATH}/include
        ${MODBUS_INCLUDE_DIRS}
)
target_link_libraries(modbus-master
#        ${MODBUS_LIBRARY}
        modbus
)

add_executable(modbus-slave
        src/modbus-slave.c
)
target_include_directories(modbus-slave PUBLIC
        ${CMAKE_PREFIX_PATH}/local/include
        ${CMAKE_PREFIX_PATH}/include
        ${MODBUS_INCLUDE_DIRS}
)
target_link_libraries(modbus-slave
#        ${MODBUS_LIBRARY}
        modbus
)

find_package(Threads)
add_executable(test_485
        src/test_485.c
)
target_include_directories(test_485 PUBLIC
        ${CMAKE_PREFIX_PATH}/local/include
        ${CMAKE_PREFIX_PATH}/include
        ${MODBUS_INCLUDE_DIRS}
)
target_link_libraries(test_485
#        ${MODBUS_LIBRARY}
        modbus
        ${CMAKE_THREAD_LIBS_INIT}
)
