#include "doc.h"
#include "sut.h"

int main()
{
  DOC doc;
  SUT sut(doc);

  sut.foo(true, true);
}
