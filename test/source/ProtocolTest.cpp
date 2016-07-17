

#include "gtest/gtest.h"

#include "dynamixel/dynamixel_proto.h"
#include "dynamixel/dynamixel_defs.h"

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

TEST_F(ProtocolTest, BuildControlPacket)
{
  EXPECT_EQ(0, 0);
}

TEST_F(ProtocolTest, ParseStatusPacket)
{
  uint8_t packet[] = {0xff, 0xff, 0xfd, 0x00, 0x03, 0x07, 0x00, 0x55, 0x00, 0x11, 0x22, 0x33, 0x3b, 0xa8};
  uint8_t length;

  uint8_t write_data[2] = {0x02, 0x00};

  uint8_t id;
  uint8_t error;
  uint8_t param_count;
  uint8_t params[16];

  int res = DXL_parse_status_pkt(sizeof(packet), packet, &id, &error, 16, &param_count, params);

  EXPECT_EQ(res, 0);
  EXPECT_EQ(id, 0x03);
  EXPECT_EQ(error, 0x00);
  EXPECT_EQ(param_count, 3);
  EXPECT_EQ(params[0], 0x11);
  EXPECT_EQ(params[1], 0x22);
  EXPECT_EQ(params[2], 0x33);
}

TEST_F(ProtocolTest, BuildPingPacket)
{
  uint8_t data[64];
  uint8_t len;

  uint8_t id = 7;
  uint16_t read_addr = 0xabcd;
  uint16_t read_len = 4;

  int res = DXL_build_ping_req(id, sizeof(data), &len, data);
  EXPECT_EQ(res, 0);

  EXPECT_EQ(data[4], id);
  EXPECT_EQ(data[5], 3);
  EXPECT_EQ(data[6], 0);
  EXPECT_EQ(data[7], DX_INSTR_PING);
}

TEST_F(ProtocolTest, BuildReadPacket)
{
  uint8_t data[64];
  uint8_t len;

  uint8_t id = 7;
  uint16_t read_addr = 0xabcd;
  uint16_t read_len = 4;

  int res = DXL_build_read_req(id, read_addr, read_len, sizeof(data), &len, data);
  EXPECT_EQ(res, 0);

  EXPECT_EQ(data[4], id);
  EXPECT_EQ(data[5], read_len + 3);
  EXPECT_EQ(data[6], 0);

  EXPECT_EQ(data[7], DX_INSTR_READ);
  EXPECT_EQ(data[8], (read_addr & 0xFF));
  EXPECT_EQ(data[9], (read_addr >> 8));
  EXPECT_EQ(data[10], (read_len & 0xFF));
  EXPECT_EQ(data[11], (read_len >> 8));
}


TEST_F(ProtocolTest, ParsePingResponsePacket)
{
  uint8_t packet[] = {0xff, 0xff, 0xfd, 0x00, 0x03, 0x07, 0x00, 0x55, 0x00, 0x11, 0x22, 0x33, 0x3b, 0xa8};
  uint8_t length;

  uint8_t write_data[2] = {0x02, 0x00};

  uint8_t id;
  uint8_t error;
  uint16_t model;
  uint8_t firmware;

  int res = DXL_parse_ping_resp(sizeof(packet), packet, &id, &error, &model, &firmware);

  EXPECT_EQ(res, 0);
  EXPECT_EQ(id, 0x03);
  EXPECT_EQ(error, 0x00);
  EXPECT_EQ(model, 0x2211);
  EXPECT_EQ(firmware, 0x33);
}

TEST_F(ProtocolTest, BuildWritePacket)
{
  uint8_t data[64];
  uint8_t length;

  int id = 1;

  uint8_t write_data[] = {0x02};

  DXL_build_write_req(id, DX_RAM_LED, sizeof(write_data), write_data,
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

  uint16_t crc = DXL_compute_crc(11, data);
  EXPECT_EQ(crc & 0xFF, data[11]);
  EXPECT_EQ(crc >> 8, data[12]);
}


