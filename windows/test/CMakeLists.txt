cmake_minimum_required(VERSION 3.1.0)

#find_package(GTest 1.10.0 CONFIG QUIET)

message("MK ${GTest_VERSION}")

if(NOT GTest_VERSION VERSION_EQUAL 1.10.0)
  include(${CMAKE_SOURCE_DIR}/cmake/external-gtest.cmake)
  # Download and unpack googletest at configure time
  configure_file(${CMAKE_SOURCE_DIR}/cmake/CMakeLists.txt.in googletest-download/CMakeLists.txt)
  execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
  if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
  endif()
  execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
  if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
  endif()

  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
    ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
    EXCLUDE_FROM_ALL)

  add_library(GTest::gtest ALIAS gtest)
  add_library(GTest::gmock ALIAS gmock)
endif()

list(REMOVE_ITEM PROD_SRC ${CMAKE_SOURCE_DIR}/src/main.cpp)

function(create_test name)
  add_executable(${name} ${name}.cpp ${PROD_SRC})
  add_test(NAME ${name} COMMAND "$<TARGET_FILE:${name}>")
  target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR}/include)

  #if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    #target_link_libraries(${name} PRIVATE gtestd.lib gmockd.lib)
  #elseif()
    #target_link_libraries(${name} PRIVATE GTest::gtest GTest::gmock)
    target_link_libraries(${name} PRIVATE gtest gmock) 
    target_compile_options(${name} PRIVATE ${COVERAGE})
    target_link_options(${name} PRIVATE ${COVERAGE})
  #endif()
endfunction()

create_test(gtest_ex1)
