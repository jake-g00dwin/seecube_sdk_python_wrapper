# TEST_RUNNER
add_library(test_fake_SeeCube
    test_fake_SeeCube.cpp    
)

target_link_libraries(test_fake_SeeCube
    ${CPPUTEST_LIBRARIES}/libCppUTest.a
    ${CPPUTEST_LIBRARIES}/libCppUTestExt.a
    fake_SeeCube
)
