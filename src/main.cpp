#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <EEPROM.h>
#include <Espfc.h>
#include <Kalman.h>
#include <Madgwick.h>
#include <Mahony.h>
#include <printf.h>
#include <blackbox/blackbox.h>
#include <EspSoftSerial.h>
#include <EspGpio.h>
#include <EscDriver.h>
#include <EspWire.h>
#include "Debug_Espfc.h"



Espfc::Espfc espfc;

    // ESP32 multicore
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    TaskHandle_t otherTaskHandle = NULL;
    extern TaskHandle_t loopTaskHandle;

    void otherTask(void *pvParameters)
    {
      espfc.load();
      espfc.beginOther();
      xTaskNotifyGive(loopTaskHandle);
      while(true)
      {
        espfc.updateOther();
      }
    }
    void setup()
    {
      disableCore0WDT();
      xTaskCreatePinnedToCore(otherTask, "otherTask", 8192, NULL, 1, &otherTaskHandle, 0); // run on PRO(0) core, loopTask is on APP(1)
      ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // wait for `otherTask` initialization
      espfc.begin();
    }
    void loop()
    {
      espfc.update();
    }



