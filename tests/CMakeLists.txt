project(Tests)

# TEST_DIRS
add_subdirectory(fake_SeeCube)
add_subdirectory(simple_test)

# TEST_RUNNER
add_executable(AllTests
    AllTests.cpp    
)

target_link_libraries(AllTests
    ${CPPUTEST_LIBRARIES}/libCppUTest.a
    ${CPPUTEST_LIBRARIES}/libCppUTestExt.a
    # TEST_LINKS
	test_fake_SeeCube
    simple_test
)
