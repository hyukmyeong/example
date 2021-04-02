#ifndef _SUT_H_
#define _SUT_H_

#include <iostream>
#include "doc.h"

class SUT {
public:
  SUT(DOC& doc) : doc_(doc) {}
  bool foo(bool, bool);

private:
  DOC& doc_;
};

#endif
