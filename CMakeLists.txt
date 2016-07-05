

# Set minimum CMake version
cmake_minimum_required(VERSION 2.8.4)
##### Project Setup #####

# Set our output target
set(TARGET dmxtest)

# Configure project and languages
project(${TARGET} C CXX ASM)

set(CMAKE_C_FLAGS "-std=gnu11 -g")
set(CMAKE_CXX_FLAGS "-std=gnu++11 -g")

# Set build
set(CMAKE_BUILD_TYPE DEBUG)

##### Modules #####

include(${PROJECT_SOURCE_DIR}/lib/dynamixel2.cmake)
add_subdirectory(${PROJECT_SOURCE_DIR}/modules/googletest/googlemock)

##### Files #####

# Add project headers
include_directories(${PROJECT_SOURCE_DIR}/test/include)

# Add project sources
set(TEST_SOURCES
    ${PROJECT_SOURCE_DIR}/test/source/main.cpp
)

##### Pre Build #####
add_custom_target(version ${PROJECT_SOURCE_DIR}/version.py LIBDYNAMIXEL2 ${CMAKE_BINARY_DIR}/version.h)
include_directories(${CMAKE_BINARY_DIR})

##### Outputs #####

# Generate executable and link
add_executable(${TARGET} ${TEST_SOURCES})
target_link_libraries(${TARGET} ${LIBS} ${OPTIONAL_LIBS})
add_dependencies(${TARGET} version)
