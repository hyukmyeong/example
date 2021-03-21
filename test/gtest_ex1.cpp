#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "doc.h"
#include "sut.h"

using namespace std;
using namespace ::testing;

class MockDOC : public DOC {
public:
  MOCK_METHOD0(foo, std::string());
};

TEST(SutTest, UseMock)
{
  // Arrange
  MockDOC mock_doc;
  SUT sut(mock_doc);

  // Expect
  EXPECT_CALL(mock_doc, foo())
    .WillRepeatedly(Return("Hello, Googletest!"));

  // Act
  bool res = sut.foo(true, true);

  // Assert
  ASSERT_TRUE(res);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
