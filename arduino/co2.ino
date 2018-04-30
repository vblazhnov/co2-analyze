#include <SoftwareSerial.h>

#define uint unsigned int

#define CMD_LEN 9
#define CO2_SENSOR_ERROR 0xff
#define MIN_VALUE 350
#define MAX_VALUE 5000

SoftwareSerial sensorSerial(5, 6); // D5 - sensor's TX, D6 - sensor's RX
const byte cmd[CMD_LEN] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
const byte offABCCmd[CMD_LEN] = {0xFF, 0x01, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x85};
byte response[CMD_LEN] = {};

uint get_co2()
{
  sensorSerial.write(cmd, CMD_LEN);
  memset(response, 0, CMD_LEN);
  sensorSerial.readBytes(response, CMD_LEN);
#if DEBUG
  Serial.println("Answer:");
  for (int i = 0; i < CMD_LEN; ++i)
  {
    Serial.print(response[i]); Serial.print(" ");
  }
  Serial.println("");
#endif
  
  if (check_response())
  {
    uint result = response[2] * 256 + response[3];
    if (result >= MIN_VALUE && result <= MAX_VALUE)
    {
      return result;
    }
  }
  
  return CO2_SENSOR_ERROR;
}

boolean check_response()
{
  if (response[0] != cmd[0] ||
      response[1] != cmd[2])
  {
    return false;
  }

  byte crc = 0;
  for (byte i = 1; i < CMD_LEN - 1; i++)
  {
    crc += response[i];
  }
  crc = 0xff - crc;
  crc++;

  return response[CMD_LEN - 1] == crc;
}

void setup_co2()
{
  sensorSerial.begin(9600);
  sensorSerial.write(offABCCmd, CMD_LEN);
}

