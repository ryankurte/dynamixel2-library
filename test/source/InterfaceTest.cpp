

#include "gtest/gtest.h"

#include "SerialInterface.hpp"

class InterfaceTest : public ::testing::Test
{
protected:
  InterfaceTest()
  {

  }

  virtual ~InterfaceTest()
  {

  }

  Dynamixel::SerialInterface si = Dynamixel::SerialInterface(NULL);;
};



TEST_F(DynamixelTest, FakeTest)
{

}

