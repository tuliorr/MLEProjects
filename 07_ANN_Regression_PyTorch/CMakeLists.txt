cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(Lab)

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(Lab Lab.cpp)
target_link_libraries(Lab "${TORCH_LIBRARIES}")
set_property(TARGET Lab PROPERTY CXX_STANDARD 14)
