cmake_minimum_required(VERSION 3.2)

project(cmake-project-practice)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)

# set(HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/division)

include_directories(${INSTALL_INCLUDE_DIR})
# include_directories(${HEADERS_DIR})

add_subdirectory(src)
add_subdirectory(test)


