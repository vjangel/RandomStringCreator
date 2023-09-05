cmake_minimum_required(VERSION 3.15.0)

set(CUSTOM_NAME Universal)

if(CUSTOM_NAME)
    set(CUSTOM_PROJECT_NAME ${CUSTOM_NAME})
else(CUSTOM_NAME)
    get_filename_component(CUSTOM_PROJECT_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
endif(CUSTOM_NAME)

project(${CUSTOM_PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

aux_source_directory(${PROJECT_SOURCE_DIR} SOURCE_FILES)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(QT_COMPONENTS
    Core
    Widgets
)
LinkQtComponents(${QT_COMPONENTS})