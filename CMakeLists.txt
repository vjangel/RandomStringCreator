cmake_minimum_required(VERSION 3.15.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Qt path
set(CMAKE_PREFIX_PATH "E:/Qt/5.15.2/mingw81_64")

# C++ build path
set(CMAKE_CXX_COMPILER "E:/Qt/Tools/mingw810_64/bin/g++.exe")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(cmakes/buildDefaults.cmake)

set(CUSTOM_NAME RandomStringCreator)

if(CUSTOM_NAME)
    set(CUSTOM_PROJECT_NAME ${CUSTOM_NAME})
else(CUSTOM_NAME)
    get_filename_component(CUSTOM_PROJECT_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
endif(CUSTOM_NAME)

project(${CUSTOM_PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

unset(CUSTOM_NAME)

add_subdirectory(Src)

# custom dependent
# file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/dependent/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin")
