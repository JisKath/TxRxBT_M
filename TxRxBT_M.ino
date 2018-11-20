/* -------------------------------------------------------- */
/* Codigo Para trabajar con el modulo Bluetooth RN-41 */

/* Codigo Para trabajar con el modulo WiFi ESP-01 */
/* -------------------------------------------------------- */


#include <SpecialFunctions.h>
#include <BT_Net.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#include <doxygen.h>
#include <ESP8266.h>
#define wifiWrite(A) wifi.send(mux_id, (uint8_t*) A, sizeof(A) - 1);

#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>


const char* SSID = "INFINITUM123C7F";
const char* PASSWORD = "01CE109E73";

int BT_On=8;
int AT_Mode=9;


int cmdOk=0;		
int	TXradioEn=0, RXradioEn=0;

String ucSerial;
String btSerial;
String TempucSerial;

SpecialFn blinkOn, blinkOff;
BT_Network disp;

ESP8266 wifi(Serial2);								// Creamos un objeto radio del tipo wifi
String wifiData="";

String msg;
String RadioWriteTemp;                  			// Array a transmitir
RF24 radio(9,53);									// Creamos un objeto radio del tipo RF24

#include "BTUCCmds.h"
#include "RadioComm_Rev1.h" 
#include "Setups.h" 
#include "wifiCmds.h" 

void setup()
{
	Serial.begin(115200);   						// Iniciar  el puerto serie
	
	Serial.println("enviando EEPROM a SRAM");		//Inicializando memoria
	disp.reeprom();
	Serial.println("EEPROM ---> SRAM");
	
	btSetup();										//Inicializando Bluetooth
	nrf24Setup();									//Inicializando NRF24
	wifiSetup();									//Inicializando ESP-01
	
	blinkOn.TON.pre=100;							//Inicilizando Timers
	blinkOff.TON.pre=100;
	blinkOn.TON.en=0;
	blinkOff.TON.en=0;
  	}
	
void loop()
{

	blinkOff.init();
	blinkOn.init();	
	blinkOn.TON.en=1;

    

	if(blinkOn.TON.tt)
		digitalWrite(13, HIGH);

	if(blinkOn.TON.dn)
		{
		digitalWrite(13, LOW);
		blinkOff.TON.en=1;
		if (blinkOff.TON.dn)
			{
			blinkOn.TON.en=0;
			blinkOff.TON.en=0;
			}
		}
		
	Duplex2Radio(TXradioEn);

}

void serialEvent(void)
  {
  if (Serial.available())
	{
	ucSerial=Serial.readString();

	ChkCMD();

	}
  }

void serialEvent1(void)
  {


  if (Serial1.available())
	{
	btSerial=Serial1.readString();
	
	if(	TXradioEn==1)
		{
		Serial.println(btSerial);
		TXradioEn=0;
		}
	
	else
	ChkCMDbt();

	}
  }

  void serialEvent2(void)
  {
  wifiRecibir();
  
  }
