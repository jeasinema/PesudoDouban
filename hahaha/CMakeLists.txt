cmake_minimum_required(VERSION 3.6)
project(oopPro)

set(CMAKE_CXX_STANDARD 11)
find_package(PkgConfig)

set(SOURCE_FILES main.cpp actor.cpp actor.hpp CRAW.cpp daily_movie.cpp movie.cpp regex.cpp url.cpp database.cpp database.h)
#dependencies
pkg_check_modules(LIB1 REQUIRED libmongocxx)
include_directories(${LIB1_INCLUDE_DIRS})
link_directories(${LIB1_LIBRARY_DIRS})
link_directories(/usr/local/opt/curl/lib/)

add_executable(oopPro ${SOURCE_FILES})

target_link_libraries(oopPro -lcurl ${LIB1_LIBRARIES} )