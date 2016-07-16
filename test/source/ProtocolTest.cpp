

#include "gtest/gtest.h"

#include "dynamixel/protocol.hpp"


using namespace Dynamixel;


class ProtocolTest : public ::testing::Test {};

void print_arr(char* name, int len, uint8_t *data)
{
  std::cout << name << ": " ;
  for (int i = 0; i < len; i++) {
    std::cout << std::hex << (int)data[i] << " ";
  }
  std::cout << std::endl;
}

TEST_F(ProtocolTest, HeaderSize)
{
  EXPECT_EQ(7, HEADER_SIZE);
  EXPECT_EQ(9, PACKET_OVERHEAD);
}

TEST_F(ProtocolTest, BuildWritePacket)
{
  uint8_t data[64];
  uint8_t length;

  int id = 1;

  uint8_t write_data[] = {0x02};

  Protocol::BuildWrite(id, DX_RAM_LED, sizeof(write_data), write_data,
                       sizeof(data), &length, data);

  EXPECT_EQ(13, length);

  EXPECT_EQ(0xff, data[0]);   // Header[0]
  EXPECT_EQ(0xff, data[1]);   // Header[1]
  EXPECT_EQ(0xfd, data[2]);   // Header[2]
  EXPECT_EQ(0x00, data[3]);   // Reserved
  EXPECT_EQ(id,   data[4]);   // Device ID
  EXPECT_EQ((length - HEADER_SIZE) & 0xFF, data[5]);   // Length LSB
  EXPECT_EQ((length - HEADER_SIZE) >> 8, data[6]);     // Length MSB

  EXPECT_EQ(DX_INSTR_WRITE, data[7]);       // Instruction (write)
  EXPECT_EQ((DX_RAM_LED & 0xFF), data[8]);  // Address LSB
  EXPECT_EQ((DX_RAM_LED >> 8), data[9]);    // Address MSB

  EXPECT_EQ(write_data[0], data[10]);

  uint16_t crc = Protocol::ComputeCRC(11, data);
  EXPECT_EQ(crc & 0xFF, data[11]);
  EXPECT_EQ(crc >> 8, data[12]);
}
#include <stdio.h>

TEST_F(ProtocolTest, ParseStatusPacket)
{
  uint8_t packet[] = {0xff, 0xff, 0xfd, 0x00, 0x03, 0x07, 0x00, 0x55, 0x00, 0x11, 0x22, 0x33, 0x3b, 0xa8};
  uint8_t length;

  uint16_t crc = Protocol::ComputeCRC(sizeof(packet) - 2, packet);

  uint8_t write_data[2] = {0x02, 0x00};

  uint8_t id;
  uint8_t error;
  uint8_t param_count;
  uint8_t params[16];

  int res = Protocol::ParseStatusPacket(sizeof(packet), packet, &id, &error, 16, &param_count, params);

  EXPECT_EQ(res, 0);
  EXPECT_EQ(id, 0x03);
  EXPECT_EQ(error, 0x00);
  EXPECT_EQ(param_count, 3);
  EXPECT_EQ(params[0], 0x11);
  EXPECT_EQ(params[1], 0x22);
  EXPECT_EQ(params[2], 0x33);

}
