#if 1
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
#else
#include <iostream>
#include <string>
#include <thread>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#if defined(MEMORY_LEAK_TEST) && defined(_MSC_VER)
#include "vld.h"
#endif

using namespace std;
using namespace ::testing;

int foo(const string& thread_name)
{
  int* ptr = new int();
}

TEST(LeakTest, Thread)
{
  thread t1(foo, "t1");
  thread t2(foo, "t2");

  t1.join();
  t2.join();
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
