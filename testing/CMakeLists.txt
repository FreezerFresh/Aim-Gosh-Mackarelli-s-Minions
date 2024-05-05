cmake_minimum_required(VERSION 3.10)

project(ActorTest)

enable_testing()

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(actor actor_testing.cc)

target_link_libraries(actor_testing ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)