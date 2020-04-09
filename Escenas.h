#ifndef Escenas_h
#define Escenas_h

#include "Arduino.h"
#include <EEPROM.h>

typedef struct dipositivos
{
	byte DispIndex;
	byte Intensidad;
};

typedef struct escena
	{
	char nombre[16];
	char t0[6];
	char t1[6];
	byte repetir;
	byte repetirAlt;
	byte habilitar;
	dipositivos Dispositivos[16];
	};



class Escenas
{
	public:
	escena Ambientes[16];
	int IndexInicio=700;
	
	void wSn(int _Index, String _Nombre);  		//Asignar Nombre a Escena _Index
	
	void wSt0(int _Index, String _t0);			//Asignar hora de inicio de dispositivo _Index 
	
	void wSt1(int _Index, String _t1);			//Asignar hora final de dispositivo _Index

	void wSeeprom(void);						//Mandar datos de escena a EEPROM
	
	void rSeeprom(void);						//Recibir datos de escena de EEPROM
	
	void clrSeeprom(void);						//Borrar ERPROM de escenas
	
};

#endif
