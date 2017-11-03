# the name of the target operating system
set(CMAKE_SYSTEM_NAME Linux)

# which architecure to compile for
set(MULTIARCH_TUPLE arm-linux-gnueabihf)

# which system root to use
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/usr/${MULTIARCH_TUPLE})

# which C and C++ compiler to use
set(CMAKE_C_COMPILER  /usr/bin/${MULTIARCH_TUPLE}-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/${MULTIARCH_TUPLE}-g++)

# where the target environment is located
set(CMAKE_FIND_ROOT_PATH /usr/${MULTIARCH_TUPLE})

# search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
set(CMAKE_LIBRARY_PATH
        /usr/lib/${MULTIARCH_TUPLE}
        /usr/lib
)