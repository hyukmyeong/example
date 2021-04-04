#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#if defined(MEMORY_LEAK_TEST) && defined(_MSC_VER)
#include "vld.h"
#endif

using namespace std;
using namespace ::testing;

void foo()
{
  char* ptr = (char*)malloc(1);
  *ptr = 0;
}

void boo()
{
  char* ptr = (char*)calloc(1, sizeof(char));
  *ptr = 0;
}

void goo()
{
  char* ptr = new char();
  *ptr = 0;
}

TEST(LeakTest, MallocCallocNew)
{
  foo();
  boo();
  goo();
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
