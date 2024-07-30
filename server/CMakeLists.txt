cmake_minimum_required(VERSION 3.10)

project(funCoin)

set(CMAKE_CXX_STANDARD 11)

# Add the source files
set(SOURCES main.cpp Server.cpp BLOCK_T&Globals.cpp)

# Add the header files
set(HEADERS Server.h BLOCK_T&Globals.h)

# Create the executable
add_executable(funCoin ${SOURCES} ${HEADERS})

# Link the zlib library
find_package(ZLIB REQUIRED)

target_link_libraries(funCoin ${ZLIB_LIBRARIES})

