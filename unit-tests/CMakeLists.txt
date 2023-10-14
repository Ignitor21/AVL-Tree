add_executable(unit-tests test.cpp)

target_link_libraries(unit-tests PRIVATE ${GTEST_LIBRARIES} PRIVATE ${CMAKE_THREAD_LIBS_INIT})

gtest_discover_tests(unit-tests)