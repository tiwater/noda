#define NODA_HEARTBEAT_MILLIS 1000

#include <noda.h>


#include <EEPROM.h>

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;
/*
NODA_DEVICE_LIST {
    //NODA_DEVICE_ADD(noda_ntc_sensor, .name="ntc", .pin=3, .chn=3, .vref=3300)
//    NODA_DEVICE_ADD(silan_sc7a20, .name="accel", .sda=7, .scl=6, .addr=25, .freq=100)
//    NODA_DEVICE_ADD(hx711, .name="weigh", .pwr=5, .sck=20, .dout=21, .gain=1)
//    NODA_DEVICE_ADD(ws2812rmt, .name="led", .pin=10, .chn=0, .nums=6)
};
*/
int noda_startup(void) {
    /*
    for (int i = 0; i < argc; ++i) {
        noda_print("%s ", argv[i]);
    }
    */
   
    
    // initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
    //return NODA_OK;
}
/*
int noda_cleanup(void) {
    noda_device_center_cleanup();
    noda_logd("noda_cleanup");
    return NODA_OK;
}
*/
int noda_onloop(void) {
    // read a byte from the current address of the EEPROM
  value = EEPROM.read(address);

  Serial.print(address);
  Serial.print("test\t");
  Serial.print(value, DEC);
  Serial.println();

  /***
    Advance to the next address, when at the end restart at the beginning.

    Larger AVR processors have larger EEPROM sizes, E.g:
    - Arduino Duemilanove: 512 B EEPROM storage.
    - Arduino Uno:         1 kB EEPROM storage.
    - Arduino Mega:        4 kB EEPROM storage.

    Rather than hard-coding the length, you should use the pre-provided length function.
    This will make your code portable to all AVR processors.
  ***/
  address = address + 1;
  if (address == EEPROM.length()) {
    address = 0;
  }

  /***
    As the EEPROM sizes are powers of two, wrapping (preventing overflow) of an
    EEPROM address is also doable by a bitwise and of the length - 1.

    ++address &= EEPROM.length() - 1;
  ***/

  delay(500);
  //return 1;
}
