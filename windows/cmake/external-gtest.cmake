include(ExternalProject)

externalproject_add(GTest
  GIT_REPOSITORY "https://github.com/google/googletest.git"
  GIT_TAG "release-1.10.0"
  PREFIX "${CMAKE_CURRENT_BINARY_DIR}/googletest"
  CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
  INSTALL_COMMAND "")

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

externalproject_get_property(GTest source_dir)
externalproject_get_property(GTest binary_dir)

add_library(GTest::gtest UNKNOWN IMPORTED)
add_library(GTest::gmock UNKNOWN IMPORTED)

add_dependencies(GTest::gtest GTest)
add_dependencies(GTest::gmock GTest)

set(LIB_PREFIX "${CMAKE_STATIC_LIBRARY_PREFIX}")
set(LIB_SUFFIX "${CMAKE_STATIC_LIBRARY_SUFFIX}")

find_package(Threads REQUIRED)

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
  set_target_properties(GTest::gtest PROPERTIES
    IMPORTED_LOCATION ${binary_dir}/lib/${LIB_PREFIX}gtestd${LIB_SUFFIX})

  set_target_properties(GTest::gmock PROPERTIES
    IMPORTED_LOCATION ${binary_dir}/lib/${LIB_PREFIX}gmockd${LIB_SUFFIX})
elseif()
  set_target_properties(GTest::gtest PROPERTIES
    IMPORTED_LOCATION ${binary_dir}/lib/gtest.lib
    IMPORTED_LINK_INTERFACE_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

  set_target_properties(GTest::gmock PROPERTIES
    IMPORTED_LOCATION ${binary_dir}/lib/gmock.lib
    IMPORTED_LINK_INTERFACE_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
endif()

include_directories(
  "${source_dir}/googletest/include"
  "${source_dir}/googlemock/include")
