#include "sut.h"
#include <iostream>

bool SUT::foo(bool param1, bool param2)
{
  if(param1 && param2) {
    std::cout << doc_.foo() << std::endl;
    return true;
  }
  return false;
}
