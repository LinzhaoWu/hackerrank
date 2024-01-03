cmake_minimum_required(VERSION 3.2)
project(myproject)

# add_subdirectory(division)
set(SOURCE_FILES main.cpp)

add_executable(practice ${SOURCE_FILES})
# target_link_libraries(practice division)
install(TARGETS practice DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})
