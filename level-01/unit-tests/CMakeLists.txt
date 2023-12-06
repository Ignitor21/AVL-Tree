add_executable(unit-tests-01 test.cpp)

target_link_libraries(unit-tests-01 PRIVATE ${GTEST_LIBRARIES} PRIVATE ${CMAKE_THREAD_LIBS_INIT})