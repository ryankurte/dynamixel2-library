

#include "gtest/gtest.h"

#include <iostream>

#include "dynamixel.hpp"

class DynamixelTest : public ::testing::Test
{
protected:

  DynamixelTest()
  {

  }

  virtual ~DynamixelTest()
  {

  }

  Dynamixel::Manager dmx = Dynamixel::Manager(NULL);;
};

TEST_F(DynamixelTest, HeaderSize)
{
  EXPECT_EQ(7, HEADER_SIZE);
  EXPECT_EQ(9, PACKET_OVERHEAD);
}

#define DXL_MAKEWORD(a, b)      ((unsigned short)(((unsigned char)(((unsigned long)(a)) & 0xff)) | ((unsigned short)((unsigned char)(((unsigned long)(b)) & 0xff))) << 8))
#define DXL_MAKEDWORD(a, b)     ((unsigned int)(((unsigned short)(((unsigned long)(a)) & 0xffff)) | ((unsigned int)((unsigned short)(((unsigned long)(b)) & 0xffff))) << 16))
#define DXL_LOWORD(l)           ((unsigned short)(((unsigned long)(l)) & 0xffff))
#define DXL_HIWORD(l)           ((unsigned short)((((unsigned long)(l)) >> 16) & 0xffff))
#define DXL_LOBYTE(w)           ((unsigned char)(((unsigned long)(w)) & 0xff))
#define DXL_HIBYTE(w)           ((unsigned char)((((unsigned long)(w)) >> 8) & 0xff))

void print_arr(char* name, int len, uint8_t *data) {
    std::cout << name << ": " ;
    for(int i=0; i<len; i++) {
        std::cout << std::hex << (int)data[i] << " ";
    }
    std::cout << std::endl;
}

TEST_F(DynamixelTest, BuildWritePacket)
{
  uint8_t data[64];
  uint8_t length;

  int id = 1;

  uint8_t write_data[2] = {0x02, 0x00};

  dmx.BuildWrite(id, Dynamixel::DX_RAM_LED, sizeof(write_data), write_data,
                 sizeof(data), &length, data);

  EXPECT_EQ(14, length);

  EXPECT_EQ(0xff, data[0]);   // Header[0]
  EXPECT_EQ(0xff, data[1]);   // Header[1]
  EXPECT_EQ(0xfd, data[2]);   // Header[2]
  EXPECT_EQ(0x00, data[3]);   // Reserved
  EXPECT_EQ(id,   data[4]);   // Device ID
  EXPECT_EQ((length - HEADER_SIZE) & 0xFF, data[5]);   // Length LSB
  EXPECT_EQ((length - HEADER_SIZE) >> 8, data[6]);     // Length MSB

  EXPECT_EQ(Dynamixel::DX_INSTR_WRITE, data[7]);       // Instruction (write)
  EXPECT_EQ((Dynamixel::DX_RAM_LED & 0xFF), data[8]);  // Address LSB
  EXPECT_EQ((Dynamixel::DX_RAM_LED >> 8), data[9]);    // Address MSB

  EXPECT_EQ(write_data[0], data[10]);   // Header[2]
  EXPECT_EQ(write_data[1], data[11]);   // Reserved

  uint16_t crc = Dynamixel::Manager::ComputeCRC(12, data);
  EXPECT_EQ(crc & 0xFF, data[12]);
  EXPECT_EQ(crc >> 8, data[13]);
}

