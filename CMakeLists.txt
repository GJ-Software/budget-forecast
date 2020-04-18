cmake_minimum_required(VERSION 3.10)
project(budget_forecast)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(budget_forecast main.cpp loadFile.cpp loadFile.h)
target_link_libraries(${CMAKE_PROJECT_NAME} ${GTKMM_LIBRARIES})
