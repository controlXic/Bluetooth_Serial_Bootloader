#include <Arduino.h>
#include "BluetoothSerial.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"

 
// Bluetooth vars //
BluetoothSerial SerialBT;
const char *pin = "4569";
String device_name = " ";
const char *blSlavePass = "sdf5431234h7r6G;"; //---> Finsihed with: ";"

// Paired Devices vars //
#define PAIR_MAX_DEVICES 20
uint8_t pairedDeviceBtAddr[PAIR_MAX_DEVICES][6];
char bda_str[18];

// Serial vars //
uint8_t rxByte = 0;
char rxStr[30] = "";
uint8_t strCnt = 0;
String tempStr = rxStr;

// Time vars //
uint32_t timeoutSerialMillis = 0;
uint16_t timeoutSerialPeriode = 200;
bool serialFlag = false;
uint32_t passTimeoutMillis = 0;
uint16_t passTimeoutPeriode = 10000;
bool passFlag = false;
uint32_t timeoutBootloaderMillis = 0;
uint16_t timeoutBootloaderPeriode = 10000;

// Bootloader vars //
#define NRST 18
#define BOOT 19
bool configMode = true;
uint8_t btlTimeout = 10;
bool btlTimeoutFlag = false;
bool clientFlag = false;


/////////////////////////////////////////////////////////////////
// Remove paired devices 
/////////////////////////////////////////////////////////////////
bool initBluetooth()
{
  if(!btStart()) {
    // Serial.println("Failed to initialize controller");
    return false;
  }
 
  if(esp_bluedroid_init() != ESP_OK) {
    // Serial.println("Failed to initialize bluedroid");
    return false;
  }
 
  if(esp_bluedroid_enable() != ESP_OK) {
    // Serial.println("Failed to enable bluedroid");
    return false;
  }
  return true;
}


void unpaired_devices()
{
  initBluetooth();

  int count = esp_bt_gap_get_bond_device_num();

  if(!count) 
  {
    //  Serial.println("No bonded device found.");
  } 
  else 
  {
    // Serial.println("Bonded device count: "); 
    // Serial.println(count);

    if(PAIR_MAX_DEVICES < count) 
    {
      count = PAIR_MAX_DEVICES; 
    }

    esp_err_t tError =  esp_bt_gap_get_bond_device_list(&count, pairedDeviceBtAddr);
    
    if(ESP_OK == tError) 
    {
      for(int i = 0; i < count; i++) 
      {  
        esp_err_t tError = esp_bt_gap_remove_bond_device(pairedDeviceBtAddr[i]);
        
        if(ESP_OK == tError) 
        {
          // Serial.print("Removed bonded device # "); 
        } 
        else 
        {
          // Serial.print("Failed to remove bonded device # ");
        }
        // Serial.println(i);
      }        
    }
  }
}

/////////////////////////////////////////////////////////////////
// Diconnect device 
/////////////////////////////////////////////////////////////////
void disconnect_bl_btl_dev()
{
  passFlag = false;
  SerialBT.disconnect();
}

/////////////////////////////////////////////////////////////////
// Reset device 
/////////////////////////////////////////////////////////////////
void reset_ESP32()
{
   ESP.restart();
}


/////////////////////////////////////////////////////////////////
// Setup
///////////////////////////////////////////////////////////////// 
void setup() 
{
  // PULL_DOWN elimina soroll del SERIAL2 //
  pinMode(16, INPUT);  
  gpio_pulldown_en(GPIO_NUM_16);

  pinMode(NRST, OUTPUT);  
  pinMode(BOOT, OUTPUT);  
  digitalWrite(NRST, LOW);
  digitalWrite(BOOT, HIGH);
  
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8E1);

  SerialBT.begin(device_name); 
  SerialBT.setPin(pin);


  // Print Bluetooth MAC address //
  const uint8_t* mac = esp_bt_dev_get_address();
  char macStr[18];
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.print("Bluetooth MAC Address: ");
  Serial.println(macStr);
}

/////////////////////////////////////////////////////////////////
// Loop
/////////////////////////////////////////////////////////////////
void loop() 
{

  //////////////////////////////
  // Config & connection mode //
  if(configMode == true)
  {

    if(SerialBT.available() > 0)
    {
      rxByte = SerialBT.read();

      rxStr[strCnt++] = rxByte;
      timeoutSerialMillis = millis();
      serialFlag = true;

      if(strCnt >= 29 || rxByte == ';')
      {
        //Serial.println(rxStr);
        
        // Connecta al router si la contrasenya es correcte //
        if(!strcmp(rxStr, blSlavePass) && passFlag == true)
        {
          // Serial.println("Connected Successfully!");
          SerialBT.print("Slave_connection_success;");
          passFlag = false;
        }

        // Activa bootloader amb el temps seleccionat a l'interface //
        else if(!strcmp(rxStr, "start_bootloader;"))
        {
          // Serial.println("Start bootloader mode.");
          btlTimeoutFlag = true;
        }
        // Llegeix el temps seleccionat //
        else if(rxStr[2] == ';' && btlTimeoutFlag == true)
        {
          tempStr = rxStr;
          btlTimeout = strtol(tempStr.substring(0, 2).c_str(), NULL, 10);
          // Serial.printf("Stop bootloader in %d seconds timeout\r\n", btlTimeout);

          timeoutBootloaderPeriode = btlTimeout * 1000;
          btlTimeoutFlag = false;
          configMode = false;
          timeoutBootloaderMillis = millis();

          // STM32 GPIO BOOT = ON
          // STM32 GPIO RST = ON
          // STM32 GPIO RST = OFF
          digitalWrite(NRST, HIGH);
          digitalWrite(BOOT, LOW);
          delay(500);
          digitalWrite(NRST, LOW);
        }

        else if(!strcmp(rxStr, "rest_before_discover;"))
        {
          reset_ESP32();
        }

        // Clean string vars //
        strCnt = 0;
        for(int i = 0; i < 30; i++)
          rxStr[i] = 0;

      }
    }

    if(SerialBT.hasClient() && clientFlag == false)
    {
      // Serial.println("Device connected!");
      // Serial.println(SerialBT.hasClient());

      // Serial.println("Enter password");
      passFlag = true;
      clientFlag = true;
      passTimeoutMillis = millis();
    }

    if(!SerialBT.hasClient() && clientFlag == true)
    {
      // Serial.println("Device not connected");
      // Serial.println(SerialBT.hasClient());

      disconnect_bl_btl_dev();
      passFlag = false;
      clientFlag = false;
      unpaired_devices();    
    }
        
    // Timeout pass connect //
    if(millis() >= passTimeoutMillis + passTimeoutPeriode && passFlag == true)
    {
      // Serial.println("Password incorrect");
      // Serial.println("Device not connected");
      // Serial.println("Now, unpair all devices");
      disconnect_bl_btl_dev();
      passFlag = false;
      clientFlag = false;
      unpaired_devices();

      // STM32 GPIO BOOT = OFF
      // STM32 GPIO RST = OFF
          digitalWrite(NRST, HIGH);
          delay(500);
          digitalWrite(NRST, LOW);      
          digitalWrite(BOOT, HIGH);
    }

    // Timeout serial receive trash //
    if(millis() >= timeoutSerialMillis + timeoutSerialPeriode && serialFlag == true)
    {
      // Clean string vars //
      for(int i = 0; i < 30; i++)
        rxStr[i] = 0;
      
      strCnt = 0;
      serialFlag = false;
    }
  }



  /////////////////////
  // Bootloader mode //
  else
  {
    if(Serial2.available() > 0)
    {
      SerialBT.write(Serial2.read());   
      
      // Reset timeout Flash mode //
      timeoutBootloaderMillis = millis();
    }
    
    if(SerialBT.available() > 0)
    {
      Serial2.write(SerialBT.read());  
      
      // Reset timeout Flash mode //
      timeoutBootloaderMillis = millis();  
    }

    // Timeout Flash mode, si no rep res en n segons surt del mode bootloader //
    if(millis() >= timeoutBootloaderMillis + timeoutBootloaderPeriode)
    {
      configMode = true;
      // Serial.println("Stop bootloader mode");

      // STM32 GPIO BOOT = OFF
      // STM32 GPIO RST = OFF
      digitalWrite(NRST, HIGH);
      delay(500);
      digitalWrite(NRST, LOW);
      digitalWrite(BOOT, HIGH);
    }
  }


}



















 
