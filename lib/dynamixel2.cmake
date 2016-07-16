# Libdynamixel2 include file

# Add library includes
include_directories(${CMAKE_CURRENT_LIST_DIR})

# Add project sources
set(LIBDYNAMIXEL2_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/source/dynamixel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/protocol.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/SerialInterface.cpp
)

# Create library
add_library(dynamixel2 ${LIBDYNAMIXEL2_SOURCES})

set(OPTIONAL_LIBS dynamixel2 ${OPTIONAL_LIBS})