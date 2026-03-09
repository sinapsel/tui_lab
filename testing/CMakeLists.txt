cmake_minimum_required(VERSION 3.12)

project(testing 
    VERSION 1.0.0
    DESCRIPTION "Simple Testing Framework"
    LANGUAGES C
)

include(GNUInstallDirs)

set(CMAKE_C_STANDARD 17)
set (SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (INC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (LIB ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB})

add_library(testing STATIC
    ${SRC}/assertions.c
    ${SRC}/testing.c
)

target_include_directories(testing PUBLIC
    ${INC}
)

add_library(mocks STATIC 
    ${SRC}/mock_abort.c
)