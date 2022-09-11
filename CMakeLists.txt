cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
project(Snake)

add_compile_options(-Wall -Wextra -pedantic -Werror)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    ${CMAKE_PROJECT_NAME}-test
    src/Snake.cpp
    test/TestSnake.cpp
)
target_link_libraries(
    ${CMAKE_PROJECT_NAME}-test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME}-test)
