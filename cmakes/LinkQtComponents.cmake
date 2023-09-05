
function(LinkQtComponents)
    if(ARGN)
        find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS ${ARGN})
        find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS ${ARGN})

        foreach(component IN LISTS ARGN)
            target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::${component})
        endforeach(component)
    endif(ARGN)
endfunction(LinkQtComponents)


function(AddModule)
    if(ARGN)
        message(STATUS "_______ ${ARGN} _________")
        foreach(MODULE IN LISTS ${ARGN})
            message(STATUS "[Loading] [Module] ${MOUDLE}...")
            add_subdirectory(${MODULE})
            get_filename_component(LIB_NAME ${MODULE} NAME)
            target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${LIB_NAME})
        endforeach(MODULE)
    endif(ARGN)
endfunction(AddModule)
