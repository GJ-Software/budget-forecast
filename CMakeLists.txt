cmake_minimum_required(VERSION 3.10)
project(budget_forecast)

set(CMAKE_CXX_STANDARD 17)


find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

file(GLOB SOURCES src/*.cpp)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/thirdparty/SQLiteCpp)
include_directories(${CMAKE_CURRENT_LIST_DIR}/thirdparty/SQLiteCpp/include)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(budget_forecast ${SOURCES})
target_link_libraries(budget_forecast
        SQLiteCpp
        sqlite3
        pthread
        dl
        ${GTKMM_LIBRARIES}
        )



