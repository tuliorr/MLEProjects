cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(xgboost-example LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

find_package(dmlc CONFIG REQUIRED)
find_package(xgboost CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)
find_package(OpenMP REQUIRED)
find_package(Threads REQUIRED)

set(PREDICT "predict")

add_executable(${PREDICT} ${CMAKE_CURRENT_SOURCE_DIR}/projeto8.cpp)

set_target_properties(
    ${PREDICT}
        PROPERTIES
            CXX_STANDARD 11
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
)
target_link_libraries(
    ${PREDICT}
        PRIVATE
            xgboost::xgboost
            dmlc::dmlc
            cxxopts::cxxopts
            OpenMP::OpenMP_CXX
            Threads::Threads
)

if(MSVC)
    target_compile_options(${PREDICT} PRIVATE /W4)
else()
    target_compile_options(${PREDICT} PRIVATE -Wall -Wextra)
endif()

