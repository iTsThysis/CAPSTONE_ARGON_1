/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/darwinwang/Documents/IoT/CAPSTONE_ARGON_1/src/CAPSTONE_ARGON_1.ino"
void displaySetup();
void setup();
void loop();
#line 1 "/Users/darwinwang/Documents/IoT/CAPSTONE_ARGON_1/src/CAPSTONE_ARGON_1.ino"
SYSTEM_MODE(MANUAL)
SYSTEM_THREAD(ENABLED)

#include "oled-wing-adafruit.h"
OledWingAdafruit display;

const size_t UART_TX_BUF_SIZE = 20;
void onDataReceived(const uint8_t *data, size_t len, const BlePeerDevice &peer, void *context);
const BleUuid serviceUuid("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
const BleUuid rxUuid("6E400002-B5A3-F393-E0A9-E50E24DCCA9E");
const BleUuid txUuid("6E400003-B5A3-F393-E0A9-E50E24DCCA9E");
BleCharacteristic txCharacteristic("tx", BleCharacteristicProperty::NOTIFY, txUuid, serviceUuid);
BleCharacteristic rxCharacteristic("rx", BleCharacteristicProperty::WRITE_WO_RSP, rxUuid, serviceUuid, onDataReceived, NULL);

//setting clean display
void displaySetup()
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
}


void setup()
{
  display.setup();
  displaySetup();
  display.setTextColor(WHITE);
  display.display();
  display.println("DISPLAY CONNECTED");
  display.display();
  delay(2000);
  displaySetup();
  display.display();


  BLE.on();
  BLE.addCharacteristic(txCharacteristic);
  BLE.addCharacteristic(rxCharacteristic);
  BleAdvertisingData data;
  data.appendServiceUUID(serviceUuid);
  data.appendLocalName("deviceID");
  BLE.advertise(&data);
  
  
  //allowing code to control argon rgb
  RGB.control(true);
  
  //initialize display
  
}

void loop()
{
  display.loop();
  if (BLE.connected())
  {
    //setting color to blue
    RGB.color(0, 0, 255);
    
    /*uint8_t txBuf[UART_TX_BUF_SIZE];
    String message = "Hello!\n";
    message.toCharArray((char *)txBuf, message.length() + 1);
    txCharacteristic.setValue(txBuf, message.length() + 1);*/

  } else {
    RGB.color(255, 255, 0);
  }
  delay(1000);
}
//receiving data
void onDataReceived(const uint8_t *data, size_t len, const BlePeerDevice &peer, void *context) {
  for (size_t i = 0; i < len; i++) {
    Serial.write(data[i]);
    if (data[i] == 49) {
      displaySetup();
      display.println("Phone sent a new message");
      display.display();
      delay(2000);
      displaySetup();
      display.display();
    } else if (data[i] == 48) {
      RGB.color(255, 255, 0);
      BLE.disconnect();
      
    }
  }
}