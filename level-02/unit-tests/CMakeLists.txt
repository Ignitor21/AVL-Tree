add_executable(unit-tests-02 test.cpp)

target_link_libraries(unit-tests-02 PRIVATE ${GTEST_LIBRARIES} PRIVATE ${CMAKE_THREAD_LIBS_INIT})

gtest_discover_tests(unit-tests-02)