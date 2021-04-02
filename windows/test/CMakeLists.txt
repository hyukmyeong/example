cmake_minimum_required(VERSION 3.1.0)

#find_package(GTest 1.10.0 CONFIG QUIET)

#if(NOT GTest_VERSION VERSION_EQUAL 1.10.0)
  include(${CMAKE_SOURCE_DIR}/cmake/external-gtest.cmake)
  #endif()

list(REMOVE_ITEM PROD_SRC ${CMAKE_SOURCE_DIR}/src/main.cpp)

function(create_test name)
  if(FALSE)
    add_executable(${name} ${name}.cpp ${PROD_SRC})
    target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(${name} PRIVATE GTest::gtest GTest::gmock)
    target_compile_options(${name} PRIVATE ${COVERAGE})

    add_test(NAME ${name} COMMAND "$<TARGET_FILE:${name}>")
  elseif()
    function(create_test name)
      add_executable(${name} ${name}.cpp ${PROD_SRC})
      target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
      #target_link_libraries(${name} PRIVATE GTest::gtest GTest::gmock)
      target_include_directories(${name} PRIVATE
        ${CMAKE_SOURCE_DIR}/../googletest/src/GTest/googletest/include
        ${CMAKE_SOURCE_DIR}/../googletest/src/GTest/googlemock/include)
      target_link_libraries(${name} PRIVATE 
        ${CMAKE_SOURCE_DIR}/../googletest/src/GTest/out/build/x64-Debug/lib/gtestd.lib
        ${CMAKE_SOURCE_DIR}/../googletest/src/GTest/out/build/x64-Debug/lib/gmockd.lib)
      target_compile_options(${name} PRIVATE ${COVERAGE})
      target_link_options(${name} PRIVATE ${COVERAGE})

      add_test(NAME ${name} COMMAND "$<TARGET_FILE:${name}>")
    endfunction()
  endif()
endfunction()

create_test(gtest_ex1)
