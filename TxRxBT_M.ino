/* -------------------------------------------------------- */
/* Codigo Para trabajar con el modulo Bluetooth RN-41 */
/* -------------------------------------------------------- */


#include <SpecialFunctions.h>
#include <BT_Net.h>
#include <SoftwareSerial.h>   		// Incluimos la librería  SoftwareSerial  
#include <EEPROM.h>

//#include <nRF24L01.h>
//#include <RF24.h>
//#include <RF24_config.h>
//#include <SPI.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"


int BT_On=8;
int AT_Mode=9;


int cmdOk=0;		
int	TXradioEn=0, RXradioEn=0;

String ucSerial;
String btSerial;
String TempucSerial;

SpecialFn timer2, timer3;
BT_Network disp;

String msg;
String RadioWriteTemp;                  // Array a transmitir
RF24 radio(9,53);                        // Creamos un objeto radio del tipo RF2$

#include "BTUCCmds.h"
#include "RadioComm_Rev1.h" 

void setup()
{
	delay(2000);
	pinMode(13, OUTPUT);
	pinMode(BT_On, OUTPUT);			// configurar pin para alimentacion modulo BT 
	pinMode(AT_Mode, OUTPUT);		// configurar pin para habilitacion de modo AT 2

	digitalWrite(AT_Mode, LOW);
	digitalWrite(BT_On, LOW);
	
	Serial.begin(115200);   			// Iniciar  el puerto serie
	Serial.println("Levantando el modulo Bluetooth");

	digitalWrite(BT_On, HIGH);
	delay(1500);
	
	digitalWrite(AT_Mode, HIGH);	
	delay(500);
	digitalWrite(AT_Mode, LOW);
	
	
	Serial.println("Esperando comandos AT:");	
	Serial1.begin(115200);       			// Iniciar el puerto serie BT

	Serial1.println("AT+NAME=BT_Master");
	
	Serial.println("enviando EEPROM a SRAM");	//Inicializando memoria
	disp.reeprom();
	Serial.println("EEPROM ---> SRAM");
	
	pinMode(53, OUTPUT);
	radio.begin();
	Serial.println("Levantando el modulo de radio NRF");

	radio.setDataRate(RF24_250KBPS);
	radio.setChannel(30);
	radio.setPALevel(3);
	radio.setRetries(15,15);  	// Maximos reintentos 
	radio.setPayloadSize(16);   // Reduce el payload de 32 si tienes problemas
	radio.openWritingPipe(selectPipe(disp.Dispositivo[0].direccion));          // Abrir para escribir
	
	timer2.TON.pre=100;
	timer3.TON.pre=100;
	timer2.TON.en=0;
	timer3.TON.en=0;
	}
	
void loop()
{

	timer3.init();
	timer2.init();	
	timer2.TON.en=1;	

	if(timer2.TON.tt)
		digitalWrite(13, HIGH);

	if(timer2.TON.dn)
		{
		digitalWrite(13, LOW);
		timer3.TON.en=1;
		if (timer3.TON.dn)
			{
			timer2.TON.en=0;
			timer3.TON.en=0;
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

