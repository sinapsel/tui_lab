cmake_minimum_required(VERSION 3.10)

add_library(mocks STATIC 
    canvas.c
)

set(MOCK_CUSTOM_FLAGS
    "LINKER:--wrap,draw_text"
    PARENT_SCOPE
)
