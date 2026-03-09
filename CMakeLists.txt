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





add_library(app_lib STATIC 
    src/controller.c
    src/models/shape.c
    src/models/rectangle.c
    src/models/circle.c
    src/models/triangle.c
    src/view.c
)
target_include_directories(app_lib 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(app_lib m)





add_executable(shape_mvc
    src/main.c
)
target_include_directories(shape_mvc PRIVATE
    include
)
target_link_libraries(shape_mvc ${NCURSESW_LIB})
target_link_libraries(shape_mvc m)
target_link_libraries(shape_mvc app_lib)



enable_testing()
set(TESTING_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/testing/lib")
find_library(TESTING_FRAMEWORK_LIB 
    NAMES testing
    PATHS ${TESTING_LIB_DIR}
    REQUIRED
    NO_DEFAULT_PATH
)
find_library(TESTING_MOCKS_LIB
    NAMES mocks
    PATHS ${TESTING_LIB_DIR}
    REQUIRED
    NO_DEFAULT_PATH
)
find_path(TESTING_INCLUDE_DIR 
    NAMES "testing.h" "assertions.h"
    PATHS "${CMAKE_CURRENT_SOURCE_DIR}/testing/include"
    REQUIRED
)

add_executable(test_model
    tests/test_model.c
    tests/main.c
)

target_include_directories(test_model 
    PRIVATE
    ${TESTING_INCLUDE_DIR}               # Заголовки фреймворка тестирования
    ${CMAKE_CURRENT_SOURCE_DIR}/include  # Заголовки тестируемой библиотеки
)

target_link_libraries(test_model 
    PRIVATE
    app_lib                     # Тестируемая библиотека
    ${TESTING_FRAMEWORK_LIB}    # Кастомный фреймворк тестирования
)
target_link_options(test_model PRIVATE 
    "LINKER:--wrap,abort"
)
target_link_libraries(test_model
    PRIVATE
    ${TESTING_MOCKS_LIB}
)
add_test(NAME test_model COMMAND test_model)