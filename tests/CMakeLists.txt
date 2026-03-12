add_subdirectory(mocks)

function(add_test_executable name sources)
    t3st_add(${name} ${sources})

    target_link_libraries(${name} PRIVATE 
        mocks
    )
    target_link_options(${name} PRIVATE 
        ${MOCK_CUSTOM_FLAGS}
    )
endfunction()


add_test_executable(test_model 
    test_model.c
)
add_test_executable(test_model_circle
    test_model_circle.c
)