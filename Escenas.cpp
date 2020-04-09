#include "Escenas.h"

void Escenas::wSn(int Index, String Nombre)
{
	for (int i = 0; i < 16; i++)
		Ambientes[Index].nombre[i]=Nombre[i];
}

void Escenas::wSt0(int Index, String t0)
{
	for (int i = 0; i < 6; i++)
		Ambientes[Index].t0[i]=t0[i];
}

void Escenas::wSt1(int Index, String t1)
{
	for (int i = 0; i < 6; i++)
		Ambientes[Index].t1[i]=t1[i];
}

void Escenas::wSeeprom(void)
{
	int j=0;											//Escribiendo Ambientes a eeprom
	
	for (int i = IndexInicio ; i < (1010+IndexInicio) ; i=i+65)
	{
		EEPROM.put(i,Ambientes[j]);
		delay(1);
		j=j+1;
	}	
}

void Escenas::rSeeprom(void)
{
	int j=0;											//Escribiendo DIspositivo a eeprom
	
	for (int i = IndexInicio ; i < (1010+IndexInicio) ; i=i+65)
	{
		EEPROM.get(i,Ambientes[j]);
		delay(1);
		j=j+1;
	}	
}

void Escenas::clrSeeprom(void)
{
	for (int i = IndexInicio ; i < (1010+IndexInicio); i++)
	{
	EEPROM.write(i, 0);
	delay(1);
	}
	
}
