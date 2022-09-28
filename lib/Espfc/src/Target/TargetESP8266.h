#pragma once

#define ESPFC_I2C_0
#define ESPFC_I2C_0_SCL 5  // D1
#define ESPFC_I2C_0_SDA 4  // D2

#define ESPFC_OUTPUT_COUNT 4
#define ESPFC_OUTPUT_0 0   // D3
#define ESPFC_OUTPUT_1 14  // D5
#define ESPFC_OUTPUT_2 12  // D6
#define ESPFC_OUTPUT_3 15  // D8

#define ESPFC_INPUT
#define ESPFC_INPUT_PIN 13  // D7

#define ESPFC_SERIAL_COUNT 2

#define ESPFC_SERIAL_0
#define ESPFC_SERIAL_0_TX 1
#define ESPFC_SERIAL_0_RX 3
#define ESPFC_SERIAL_0_FN (SERIAL_FUNCTION_MSP)
#define ESPFC_SERIAL_0_BAUD (SERIAL_SPEED_115200)
#define ESPFC_SERIAL_0_BBAUD (SERIAL_SPEED_NONE)

#define ESPFC_SERIAL_1
#define ESPFC_SERIAL_1_TX 2  // D4
#define ESPFC_SERIAL_1_RX -1
#define ESPFC_SERIAL_1_FN (SERIAL_FUNCTION_NONE)
#define ESPFC_SERIAL_1_BAUD (SERIAL_SPEED_115200)
#define ESPFC_SERIAL_1_BBAUD (SERIAL_SPEED_NONE)

#define ESPFC_SERIAL_SOFT_0
#define ESPFC_SERIAL_SOFT_0_FN (SERIAL_FUNCTION_NONE)
#define ESPFC_SERIAL_SOFT_0_RX

#define ESPFC_BUZZER
#define ESPFC_BUZZER_PIN 16  // D0

#define ESPFC_ADC_0
#define ESPFC_ADC_0_PIN 17   // A0

#define ESPFC_FEATURE_MASK (FEATURE_RX_PPM | FEATURE_DYNAMIC_FILTER)

#define ESPFC_OUTPUT_PROTOCOL ESC_PROTOCOL_DISABLED

#define ESPFC_GUARD 1
#define ESPFC_GYRO_DENOM_MAX 4
#define ESPFC_WIFI_ALT

//#define ESPFC_LOGGER_FS // deprecated
#define ESPFC_LOGGER_FS_ALT

#define ESPFC_DEBUG_PIN D0

#define SERIAL_RXD_INV (1  <<  UCRXI) // bit 19 - invert rx
#define SERIAL_TXD_INV (1  <<  UCTXI) // bit 22 - invert tx
#define SERIAL_TX_FIFO_SIZE 0x80

#define ESPFC_SERIAL_INIT(dev, sc, conf) \
  if(conf.inverted) {\
    sc |= (SERIAL_RXD_INV | SERIAL_TXD_INV);\
  }\
  dev.begin(conf.baud, (SerialConfig)sc);\

#define ESPFC_SPI_INIT(dev, sck, mosi, miso, ss) \
  dev.pins(sck, mosi, miso, ss); \
  dev.begin(); \

#if !defined(ESPFC_REVISION) // development build
  #undef ESPFC_OUTPUT_PROTOCOL
  #define ESPFC_OUTPUT_PROTOCOL ESC_PROTOCOL_DSHOT150

  #undef ESPFC_SERIAL_1_FN
  #define ESPFC_SERIAL_1_FN (SERIAL_FUNCTION_BLACKBOX)

  #undef ESPFC_SERIAL_1_BBAUD
  #define ESPFC_SERIAL_1_BBAUD (SERIAL_SPEED_250000)
#endif

namespace Espfc {

inline uint32_t getBoardId0()
{
  return ESP.getChipId();
}

inline uint32_t getBoardId1()
{
  return ESP.getFlashChipId();
}

inline uint32_t getBoardId2()
{
  return ESP.getFlashChipSize();
}

inline void targetReset()
{
  // pin setup to ensure boot from flash
  pinMode(0, OUTPUT); digitalWrite(0, HIGH); // GPIO0 to HI
  pinMode(2, OUTPUT); digitalWrite(2, HIGH); // GPIO2 to HI
  pinMode(15, OUTPUT); digitalWrite(15, LOW); // GPIO15 to LO
  pinMode(0, INPUT);
  pinMode(2, INPUT);
  pinMode(15, INPUT);
  ESP.reset();
  while(1) {}
}

};