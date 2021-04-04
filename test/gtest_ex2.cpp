#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#if defined(FIND_LEAK) && defined(_MSC_VER)
#include "vld.h"
#endif

using namespace std;
using namespace ::testing;

int foo()
{
  int *array = new int[100];
  delete [] array;
  return array[5];
}

TEST(ASanTest, HeapUseAfterFree)
{
  foo();
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
