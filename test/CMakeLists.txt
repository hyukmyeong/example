cmake_minimum_required(VERSION 3.1.0)

find_package(GTest 1.10.0 CONFIG REQUIRED)

list(REMOVE_ITEM PROD_SRC ${CMAKE_SOURCE_DIR}/src/main.cpp)

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
  function(create_test name)
    add_executable(${name} ${name}.cpp ${PROD_SRC})
    add_test(NAME ${name} COMMAND "$<TARGET_FILE:${name}>")
    target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(${name} PRIVATE GTest::gtest GTest::gmock)

    if(FALSE)
      target_compile_options(${name} PRIVATE /fsanitize=address)
      target_link_options(${name} PRIVATE /incremental:no)
    endif()

    if(FALSE)
      target_compile_definitions(${name} PRIVATE MEMORY_LEAK_TEST)
      target_link_libraries(${name} PRIVATE "C:/Program Files (x86)/Visual Leak Detector/lib/Win64/vld.lib")
      target_include_directories(${name} PRIVATE "C:/Program Files (x86)/Visual Leak Detector/include")
    endif()
  endfunction()
elseif(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  find_program(GCOV ${CMAKE_LIBRARY_ARCHITECTURE}-gcov)
  find_program(LCOV lcov)
  find_program(GENH genhtml)

  if(GCOV AND LCOV AND GENH)
    set(COVERAGE "-coverage")
    add_custom_target(coverage
      COMMAND ${LCOV} -c -d '.' -o 'info'
      COMMAND ${LCOV} -e 'info' '*/example/*' -o 'info'
      COMMAND ${LCOV} -r 'info' '*/test/*' -o 'info'
      COMMAND ${GENH} 'info' -o 'coverage' --filter branch)
  endif()

  function(create_test name)
    add_executable(${name} ${name}.cpp ${PROD_SRC})
    target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(${name} PRIVATE GTest::gtest GTest::gmock)
    target_compile_options(${name} PRIVATE ${COVERAGE} -fsanitize=address)
    target_link_options(${name} PRIVATE ${COVERAGE} -fsanitize=address)
  
    if(NOT CMAKE_CROSSCOMPILING)
      add_test(NAME ${name} COMMAND "$<TARGET_FILE:${name}>")
    else()
      add_test(NAME ${name} COMMAND
      env ASAN_OPTIONS=detect_leaks=0
      ${CMAKE_CROSSCOMPILING_EMULATOR} -L ${CMAKE_FIND_ROOT_PATH} "$<TARGET_FILE:${name}>")

      if(FALSE)
        set(name_ "${name}_leak")
        add_executable(${name_} ${name}.cpp ${PROD_SRC})
        target_include_directories(${name_} PRIVATE ${CMAKE_SOURCE_DIR}/include)
        target_link_libraries(${name_} PRIVATE GTest::gtest GTest::gmock libtcmalloc.a)

        add_test(NAME ${name_} COMMAND
          env HEAPCHECK=normal HEAP_CHECK_MAX_LEAKS=0
          PPROF_PATH=${CMAKE_FIND_ROOT_PATH}/bin/pprof
          ${CMAKE_CROSSCOMPILING_EMULATOR} -L ${CMAKE_FIND_ROOT_PATH} "$<TARGET_FILE:${name_}>")
      endif()
    endif()
  endfunction()
endif()

create_test(gtest_ex1)
create_test(gtest_ex2)
create_test(gtest_ex3)
