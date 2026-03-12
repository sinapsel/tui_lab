cmake_minimum_required(VERSION 3.10)
project(ShapeMVC)

set(CMAKE_C_STANDARD 17)



set(CURSES_NEED_WIDE TRUE)
add_definitions(-D_XOPEN_SOURCE_EXTENDED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

find_library(NCURSESW_LIB ncursesw)
if(NOT NCURSESW_LIB)
    message(FATAL_ERROR "ncursesw library not found")
endif()



set(APP_LIB_TARGET app_lib CACHE INTERNAL "")


add_library(${APP_LIB_TARGET} STATIC 
    src/controller.c
    src/models/shape.c
    src/models/rectangle.c
    src/models/circle.c
    src/models/triangle.c
    src/canvas.c
    src/view.c
)
target_include_directories(${APP_LIB_TARGET} 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(${APP_LIB_TARGET} m)





add_executable(shape_mvc
    src/main.c
)
target_include_directories(shape_mvc PRIVATE
    include
)
target_link_libraries(shape_mvc ${NCURSESW_LIB})
target_link_libraries(shape_mvc m)
target_link_libraries(shape_mvc ${APP_LIB_TARGET})



enable_testing()
add_subdirectory(t3sting)
add_subdirectory(tests)