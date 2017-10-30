# the name of the target operating system
set(CMAKE_SYSTEM_NAME Linux)

# which system root to use
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/usr/arm-linux-gnueabihf)

# which C and C++ compiler to use
set(CMAKE_C_COMPILER  /usr/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabihf-g++)

# here is the target environment located
set(CMAKE_FIND_ROOT_PATH /usr/arm-linux-gnueabihf)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
set(CMAKE_LIBRARY_PATH
        /usr/lib/arm-linux-gnueabihf
        /usr/lib
)