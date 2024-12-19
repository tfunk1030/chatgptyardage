cmake_minimum_required(VERSION 3.26.4)
project(GolfPhysics)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define M_PI if not defined
add_definitions(-D_USE_MATH_DEFINES)

# Download and build GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add source files
set(SOURCES
    src/physics/trajectory.cpp
    src/physics/wind.cpp
    src/physics/physics.cpp
)

# Create library
add_library(golf-physics ${SOURCES})

# Add include directories
target_include_directories(golf-physics PUBLIC include)

# Add test executable
add_executable(physics_tests
    tests/physics/unit/trajectory_test.cpp
    tests/physics/unit/wind_test.cpp
    tests/physics/integration/physics_integration_test.cpp
)

# Link test executable with Google Test and our library
target_link_libraries(physics_tests
    golf-physics
    GTest::gtest_main
)

# Enable testing
enable_testing()
add_test(NAME physics_tests COMMAND physics_tests)
