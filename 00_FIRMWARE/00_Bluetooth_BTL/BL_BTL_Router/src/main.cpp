/*

ESP_BT_CONNECTABLE
ESP_BT_NON_CONNECTABLE
ESP_BT_GENERAL_DISCOVERABLE
ESP_BT_LIMITED_DISCOVERABLE
ESP_BT_NON_DISCOVERABLE

*/


#include <Arduino.h>
#include "BluetoothSerial.h"
#include "esp_bt_main.h"


// Bluetooth vars //
BluetoothSerial SerialBT;
const char *pin = "4569"; 
String myName = " ";
const char *blSlavePass = "sdf5431234h7r6G"; 
const char *blRouterPass = "sdf546bverW1n"; 

// Paired Devices vars //
#define PAIR_MAX_DEVICES 20
uint8_t pairedDeviceBtAddr[PAIR_MAX_DEVICES][6];
char bda_str[18];

// Serial vars //
uint8_t rxByte = 0;
char rxStr[30] = "";
uint8_t strCnt = 0;
String tempStr = rxStr;
uint8_t macAddress[6]  = "";
bool readMacMode = 0;
uint8_t cntMac = 0;

// Time vars //
uint32_t timeoutSerialMillis = 0;
uint16_t timeoutSerialPeriode = 200;
bool serialFlag = false;

uint32_t timeoutBlMillis = 0;
uint16_t timeoutBlPeriode = 1000;
bool blFlag = false;

uint32_t passTimeoutMillis = 0;
uint16_t passTimeoutPeriode = 10000;
uint8_t passFlag = 0;

uint32_t timeoutBootloaderMillis = 0;
uint16_t timeoutBootloaderPeriode = 10000;

// Bootloader vars //
bool configMode = true;
uint8_t connectAttempts = 0;
uint8_t btlTimeout = 10;
bool btlTimeoutFlag = false;

uint8_t rxBlByte = 0;
char rxBlStr[30] = "";
uint8_t strBlCnt = 0;



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
     Serial.println("No bonded device found.");
  } 
  else 
  {
    Serial.print("Bonded device count: "); 
    Serial.println(count);

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
          Serial.print("Removed bonded device # "); 
        } 
        else 
        {
          Serial.print("Failed to remove bonded device # ");
        }
        Serial.println(i);
      }        
    }
  }
}

/////////////////////////////////////////////////////////////////
// Discover devices 
/////////////////////////////////////////////////////////////////
void discover_blc_devices()
{
  SerialBT.discoverAsync([](BTAdvertisedDevice* pDevice) 
  {
    Serial.printf("%s\n", pDevice->toString().c_str());
  }, 10000);
}



/////////////////////////////////////////////////////////////////
// Connect device 
/////////////////////////////////////////////////////////////////
void print_mac()
{
    Serial.printf("%X:%X:%X:%X:%X:%X", macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);
}

void connect_bl_btl_dev()
{  
  bool connected;

  macAddress[0] = strtol(tempStr.substring(0, 2).c_str(), NULL, 16);
  macAddress[1] = strtol(tempStr.substring(3, 5).c_str(), NULL, 16);
  macAddress[2] = strtol(tempStr.substring(6, 8).c_str(), NULL, 16);
  macAddress[3] = strtol(tempStr.substring(9, 11).c_str(), NULL, 16);
  macAddress[4] = strtol(tempStr.substring(12, 14).c_str(), NULL, 16);
  macAddress[5] = strtol(tempStr.substring(15, 17).c_str(), NULL, 16);

  print_mac(); 

  SerialBT.discoverAsyncStop();

  connected = SerialBT.connect(macAddress, 0, ESP_SPP_SEC_NONE, ESP_SPP_ROLE_SLAVE);
 
  if(connected) 
  {
    Serial.print("Enter BL password");
    passFlag = 1;
    passTimeoutMillis = millis();
  } 
  else 
  {
    connectAttempts++;
    if(connectAttempts >= 2)
    {
      Serial.print("Device not connected");
      return;
    }
    connect_bl_btl_dev();
  }
}

/////////////////////////////////////////////////////////////////
// Diconnect device 
/////////////////////////////////////////////////////////////////
void disconnect_bl_btl_dev()
{
  passFlag = 0;
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
  Serial.begin(115200, SERIAL_8E1);

  SerialBT.begin(myName, true);
  SerialBT.setPin(pin);
  }
 
/////////////////////////////////////////////////////////////////
// Loop
/////////////////////////////////////////////////////////////////
void loop() 
{

  /////////////////////////////////////////////////////////////////
  // Config & connection mode 
  /////////////////////////////////////////////////////////////////
  if(configMode == true)
  {    
    ///////////////////////////////
    // Serial COM with interface //
    if(Serial.available() > 0)
    {
      rxByte = Serial.read();

      // Serial.print(Serial.read());

      //  Construeix array "string" //
      rxStr[strCnt++] = rxByte;
      timeoutSerialMillis = millis();
      serialFlag = true;

      if(strCnt >= 29 || rxByte == ';')
      {
        // Serial.println(rxStr);
        
        // Connecta al interface per Serial i valida //
        if(!strcmp(rxStr, "connect_interface;"))
        {
          Serial.println("123gT88eert");
          delay(200);
          Serial.println("Serial connected to cXic BL BTL");
          Serial.print("Device start!");
        }

        // Reseteja ESP32 per fer un dicover bluetooth devices //
        else if(!strcmp(rxStr, "rest_before_discover;"))
        {
          reset_ESP32();
        }

        else if(!strcmp(rxStr, "discover_blc_devices;"))
        {
          Serial.print("Scan devices.....");
          
          discover_blc_devices();
        }

        // Es connecta al device selecionat a l'interface //
        else if(!strcmp(rxStr, "connect_device;"))
        {
          Serial.print("Connect to: ");
          
          readMacMode = true;
        }
        
        // Llegeix la MAC del device seleccionat //
        else if(rxStr[2] == ':' && rxStr[5] == ':' && rxStr[8] == ':' && rxStr[11] == ':' && rxStr[14] == ':' && readMacMode == true)
        {
          tempStr = rxStr;
          readMacMode = false;
          connectAttempts = 0;
          
          connect_bl_btl_dev();
        }

        // Espera la contrasenya a enviar al BL dev Slave (falta construir codi...)//
        else if(/*!strcmp(rxStr, "sdf546bverW1n;") &&*/ passFlag == 1)
        {
          //Serial.print("Connected Successfully!");
          passFlag = 2;

          delay(500);
          SerialBT.print(rxStr); 
        }

        // Desconnecta Router i Salve //
        else if(!strcmp(rxStr, "disconnect_device;"))
        {
          Serial.print("Disconnect from: ");

          disconnect_bl_btl_dev();
          print_mac();
          Serial.println();
          unpaired_devices();
        }
        
        // Activa bootloader amb el temps seleccionat a l'interface //
        else if(!strcmp(rxStr, "start_bootloader;"))
        {         
          if(!SerialBT.hasClient())
          {
             Serial.println("BL not connected.");
            btlTimeoutFlag = false;
          }
          else
          {
            Serial.println("Start bootloader mode.");
            btlTimeoutFlag = true;

            SerialBT.print(rxStr);
          }
        }

        // Llegeix el temps seleccionat //
        else if(rxStr[2] == ';' && btlTimeoutFlag == true)
        {
          tempStr = rxStr;
          btlTimeout = strtol(tempStr.substring(0, 2).c_str(), NULL, 10);
          Serial.printf("Stop bootloader in %d seconds timeout", btlTimeout);

          timeoutBootloaderPeriode = btlTimeout * 1000;
          btlTimeoutFlag = false;
          configMode = false;
          timeoutBootloaderMillis = millis();

          SerialBT.print(rxStr); 
        }

        // Polsadors, special commands interface (TEST) //
        else if(!strcmp(rxStr, "reset_BL_BTL;"))
        {
          Serial.print("RESET BL_BTL device");

          delay(500);
          reset_ESP32();
        }

        else if(!strcmp(rxStr, "unpair_devices;"))
        {
          Serial.print("Unpair devices");
          unpaired_devices();
        }
        
        else if(!strcmp(rxStr, "test;"))
        {
          Serial.print("test");
        }

        // Clean string vars //
        strCnt = 0;
        for(int i = 0; i < 30; i++)
          rxStr[i] = 0;
      }
    }

    //////////////////////////////////
    // Timeout serial receive trash //
    if(millis() >= timeoutSerialMillis + timeoutSerialPeriode && serialFlag == true)
    {
      // Clean string vars //
      for(int i = 0; i < 30; i++)
        rxStr[i] = 0;
      
      strCnt = 0;
      serialFlag = false;
    }    
    
    //////////////////////////////
    // Bluetooth COM with Slave //
    if(SerialBT.available() > 0)
    {
    
      rxBlByte = SerialBT.read();

      // Serial.print(SerialBT.read());

      //  Construeix array "string" //
      rxBlStr[strBlCnt++] = rxBlByte;
      timeoutBlMillis = millis();
      blFlag = true;

      if(strBlCnt >= 29 || rxBlByte == ';')
      {
        if(!strcmp(rxBlStr, "Slave_connection_success;"))
        {
          Serial.print("Connected Successfully!");
          passFlag = 0;
        }

        // Clean string vars //
        strBlCnt = 0;
        for(int i = 0; i < 30; i++)
          rxBlStr[i] = 0;

      } 
    }

    /////////////////////////////////////
    // Timeout bluetooth receive trash //
    if(millis() >= timeoutBlMillis + timeoutBlPeriode && blFlag == true)
    {
      // Clean string vars //
      for(int i = 0; i < 30; i++)
        rxBlStr[i] = 0;
      
      strBlCnt = 0;
      blFlag = false;
    }    
    
    //////////////////////////
    // Timeout pass connect //
    if(millis() >= passTimeoutMillis + passTimeoutPeriode && passFlag > 0)
    {
      Serial.println("Password incorrect");
      Serial.println("Device not connected");
      Serial.println("Now, unpair all devices");
      disconnect_bl_btl_dev();
      passFlag = 0;
      unpaired_devices();
    }
  }




  ////////////////////////////////////////////////////////////////////
  // Bootloader mode 
  ////////////////////////////////////////////////////////////////////
  else
  {
    if(Serial.available() > 0)
    {
      SerialBT.write(Serial.read());   
      
      // Reset timeout Flash mode //
      timeoutBootloaderMillis = millis();
    }
    
    if(SerialBT.available() > 0)
    {
      Serial.write(SerialBT.read());  
      
      // Reset timeout Flash mode //
      timeoutBootloaderMillis = millis();  
    }

    // Timeout Flash mode, si no rep res en n segons surt del mode bootloader //
    if(millis() >= timeoutBootloaderMillis + timeoutBootloaderPeriode)
    {
      configMode = true;
      Serial.print("Stop bootloader mode");
    }
  }


}

