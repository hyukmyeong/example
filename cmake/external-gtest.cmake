include(ExternalProject)

externalproject_add(GTest
  GIT_REPOSITORY "https://github.com/google/googletest.git"
  GIT_TAG "release-1.10.0"
  PREFIX "${CMAKE_CURRENT_BINARY_DIR}/googletest"
  CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
  INSTALL_COMMAND "")

externalproject_get_property(GTest source_dir)
externalproject_get_property(GTest binary_dir)

add_library(GTest::gtest UNKNOWN IMPORTED)
add_library(GTest::gmock UNKNOWN IMPORTED)

add_dependencies(GTest::gtest GTest)
add_dependencies(GTest::gmock GTest)

find_package(Threads REQUIRED)

set_target_properties(GTest::gtest PROPERTIES
  IMPORTED_LOCATION ${binary_dir}/lib/libgtest.a
  IMPORTED_LINK_INTERFACE_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

set_target_properties(GTest::gmock PROPERTIES
  IMPORTED_LOCATION ${binary_dir}/lib/libgmock.a
  IMPORTED_LINK_INTERFACE_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

include_directories(
  "${source_dir}/googletest/include"
  "${source_dir}/googlemock/include")
