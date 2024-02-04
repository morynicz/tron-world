cmake_minimum_required(VERSION 3.12)
project(TronWorld CXX)

add_compile_options(-Wall -Wextra -pedantic -Werror)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)

FetchContent_MakeAvailable(googletest)

add_library(tronWorld src/World.cpp)
target_include_directories(tronWorld PUBLIC include)
target_compile_features(tronWorld PUBLIC cxx_std_20)

add_executable(world_test src/WorldTests.cpp)
target_compile_features(world_test PUBLIC cxx_std_20)
target_include_directories(world_test PUBLIC include)
target_link_libraries(world_test gmock_main gtest gmock tronWorld)

add_custom_target(run_tests
                  COMMAND world_test
                  DEPENDS world_test)

enable_testing()
add_test(tests hanabi_test)