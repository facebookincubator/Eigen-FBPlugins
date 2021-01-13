cmake_minimum_required(VERSION 3.10)
project(UnitTests)
enable_testing()

set(BIN_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB PLUGINS ${SRC_DIR}/Eigen*Plugin.h)
file(GLOB SRCS ${SRC_DIR}/test/*.cpp)
add_executable(test-all ${SRCS})

set(
  gtest_force_shared_crt ON
  CACHE BOOL "" FORCE
)

set(
  BUILD_GMOCK OFF
  CACHE BOOL "" FORCE
)

add_subdirectory(
  "${SRC_DIR}/googletest"
)

target_link_libraries(
  test-all
  gtest_main
  gtest
)

include_directories(${SRC_DIR}/eigen)
include_directories(${SRC_DIR})

include(GoogleTest)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # https://gcc.gnu.org/bugzilla/show_bug.cgi?id=56746
  target_compile_options(test-all PUBLIC -ftrack-macro-expansion=0)
endif()

target_compile_definitions(test-all PUBLIC EIGEN_HAS_STD_RESULT_OF)
target_compile_definitions(test-all PUBLIC EIGEN_FAIL_ON_EXPR2D)

if (${CMAKE_CXX_STANDARD} GREATER_EQUAL 17)
  target_compile_definitions(test-all PUBLIC EIGEN_HAS_CXX17)
endif()

foreach(PLUGIN_FILE ${PLUGINS})
  string(REPLACE "${SRC_DIR}/Eigen" "" PLUGIN ${PLUGIN_FILE})
  string(REPLACE "Plugin.h" "" PLUGIN ${PLUGIN})
  string(TOUPPER ${PLUGIN} PLUGIN)
  target_compile_definitions(test-all
    PUBLIC EIGEN_${PLUGIN}_PLUGIN=\"${PLUGIN_FILE}\")
endforeach(PLUGIN_FILE)

gtest_discover_tests(test-all)
