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
    src/canvas.c
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

add_subdirectory(tests/mocks)
add_subdirectory(t3sting)




add_executable(test_model 
    tests/main.c
    tests/test_model.c
)
target_link_libraries(test_model 
    PRIVATE
    app_lib         # Тестируемая библиотека
    t3st            # Кастомный фреймворк тестирования
    mocks           # Моки вызовов
)
target_link_options(test_model PRIVATE 
    "LINKER:--wrap,abort"       # Подменяем abort для t3st
    "LINKER:--wrap,draw_text"   # Кастомный мок из mocks
)
add_test(NAME test_model COMMAND test_model)




add_executable(test_model_circle 
    tests/main.c
    tests/test_model_circle.c
)
target_link_libraries(test_model_circle 
    PRIVATE
    app_lib         # Тестируемая библиотека
    t3st            # Кастомный фреймворк тестирования
    mocks           # Моки вызовов
)
target_link_options(test_model_circle PRIVATE 
    "LINKER:--wrap,abort"       # Подменяем abort для t3st
    "LINKER:--wrap,draw_text"   # Кастомный мок из mocks
)
add_test(NAME test_model_circle COMMAND test_model_circle)