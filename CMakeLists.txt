cmake_minimum_required(VERSION 3.1.0)

project(product VERSION 1.0.0 LANGUAGES CXX)

message(STATUS "Current OS       \t: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Host System      \t: ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS "Target System    \t: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "Compiler         \t: ${CMAKE_CXX_COMPILER}")
message(STATUS "Compiler ID      \t: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Compiler Version \t: ${CMAKE_CXX_COMPILER_VERSION}")

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE PROD_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${PROD_SRC})

target_include_directories(${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(
  TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})

if(NOT CMAKE_BUILD_TYPE MATCHES Release)
  enable_testing()
  add_subdirectory(test)
endif()
