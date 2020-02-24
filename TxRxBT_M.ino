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
//#define wifiWrite(A) wifi.send(mux_id, (uint8_t*) A, sizeof(A) - 1);

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const char* SSID = "INFINITUM123C7F";
const char* PASSWORD = "01CE109E73";

int BT_On=24;
int AT_Mode=23;

int fuenteCMD;


int cmdOk=0;		
int	TXradioEn=0, RXradioEn=0;

String ucSerial;
String btSerial;
String TempucSerial;

SpecialFn blinkOn, blinkOff, wifiSta;
BT_Network disp;

ESP8266 wifi(Serial2);								// Creamos un objeto radio del tipo wifi
String wifiData="";
String wifiCmd2Snd="",wifiString2Snd="";
   uint8_t mux_id;

String msg;
String RadioWriteTemp;                  			// Array a transmitir
RF24 radio(A9,53);									// Creamos un objeto radio del tipo RF24

#include "wifiCmds.h"
#include "BTUCCmds.h"
#include "PaginaHTML.h" 
#include "RadioComm_Rev1.h" 
#include "Setups.h" 

void setup()
{
	Serial.begin(115200);   						// Iniciar  el puerto serie
	
	Serial.println("enviando EEPROM a SRAM");		//Inicializando memoria
	disp.reeprom();
	Serial.println("EEPROM ---> SRAM");
	
	pinMode(A9, OUTPUT);	
	
	btSetup();										//Inicializando Bluetooth
	nrf24Setup();									//Inicializando NRF24
	wifiSetup();									//Inicializando ESP-01
	
	blinkOn.TON.pre=100;							//Inicilizando Timers
	blinkOff.TON.pre=100;
	wifiSta.TON.pre=60000;
	blinkOn.TON.en=0;
	blinkOff.TON.en=0;
	wifiSta.TON.en=0;
  	}

   
//#define wifiWrite(A) wifi.send(mux_id, (uint8_t*) A, sizeof(A) - 1);
void loop()
{
	blinkOff.init();
	blinkOn.init();
	wifiSta.init();	
	blinkOn.TON.en=1;
	wifiSta.TON.en=1;

    if(wifiSta.TON.dn){
		wifiSta.TON.en=0;
    Serial.println(wifi.getLocalIP().length());
		Serial.println("Validando wifi");
			if(wifi.getLocalIP().length()<120){
				Serial.println("wifi NOK");
				wifiSetup();
				wifiSta.TON.pre=10000;
				}
			else{
				wifiSta.TON.pre=60000;
				Serial.println("wifi OK");
			}
		}

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
	Escuchando();
	
	if(fuenteCMD==13)
	{
	//htmlPagina();
    //Serial.println("ehhh");   
		fuenteCMD=3;
    }

}

void serialEvent(void)
  {
  fuenteCMD=1;
  if (Serial.available())
	{
	ucSerial=Serial.readString();

	ChkCMD();

	}
  }

void serialEvent1(void)
  {
  
  fuenteCMD=2;

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
  ChkCMDwf();
  wifiData="";
  fuenteCMD=3;
  wifiSta.TON.en=0;


  }
