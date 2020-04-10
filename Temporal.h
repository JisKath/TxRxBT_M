
		
		
void ChkCMD(void)												//Funcion para busqueda y ejecucion de comandos tipo _XXXX
{
if(ucSerial.substring(0,1) == "_")
{
	cmdOk=0;

	if(ucSerial.substring(0,6) == "_btoff")						//Comando para apagar modulo HC-05
	{	
		digitalWrite(BT_On, LOW);
		Serial.println("Bluetooth Apagado");
		cmdOk=1;
	}

	if(ucSerial.substring(0,5) == "_bton")						//Comando para encender modulo HC-05
	{
		digitalWrite(BT_On, HIGH);
		Serial.println("Bluetooth Encendido");
		cmdOk=1;
	}

	if(ucSerial.substring(0,5) == "_aton")						//Comando para encender Pin 34 en HC-05
	{
		digitalWrite(AT_Mode, HIGH);
		Serial.println("Modo AT1 activo PIN 34");
		cmdOk=1;
	}

	if(ucSerial.substring(0,6) == "_atoff")						//Comando para apagar Pin 34 en HC-05
	{
		digitalWrite(AT_Mode, LOW);
		Serial.println("Modo AT1 apagado");
		cmdOk=1;
	}

	if(ucSerial.substring(0,4) == "_wn[")
	{
		disp.wn(ucSerial.substring(4).toInt(),ucSerial.substring(ucSerial.lastIndexOf(',')+1,ucSerial.lastIndexOf(']')));
		Serial.println("_wn OK");
		cmdOk=1;
	}
		
	if(ucSerial.substring(0,4) == "_rn[")
	{
		Serial.println(String(disp.Dispositivo[ucSerial.substring(4).toInt()].nombre));
		Serial.println("_rn OK");
		cmdOk=1;
	}


	if(ucSerial.substring(0,4) == "_wd[")
	{
		disp.wd(ucSerial.substring(4).toInt(),ucSerial.substring(ucSerial.indexOf(',')+1,ucSerial.lastIndexOf(']')));
		Serial.println("_wd OK");
		cmdOk=1;
	}

	if(ucSerial.substring(0,4) == "_rd[")
	{
		Serial.println(String(disp.Dispositivo[ucSerial.substring(4).toInt()].direccion));
		Serial.print("_rd OK");
		cmdOk=1;
	}

	if(ucSerial.substring(0,4) == "_rt[")
	{
		Serial.print("_rt OK");
		cmdOk=1;
	}
	
	if(ucSerial.substring(0,5) == "_rall")
	{
		for (int i = 0 ; i < 16 ; i++)
		{
			Serial.print(i);
			Serial.print(": ");
			Serial.print(String(disp.Dispositivo[i].nombre));
			Serial.print(", ");
			Serial.println(String(disp.Dispositivo[i].direccion));

		}
			
		Serial.println("_rall OK");
		cmdOk=1;
	}

	if(ucSerial.substring(0,8) == "_weeprom")
	{
		Serial.println("enviando SRAM --> EEPROM");
		disp.weeprom();
		Serial.println("SRAM --> EEPROM enviado");
		cmdOk=1;
	}

	if(ucSerial.substring(0,8) == "_reeprom")
	{
		Serial.println("enviando EEPROM --> SRAM");
		disp.reeprom();
		Serial.println("EEPROM ---> SRAM enviado");
		cmdOk=1;
	}
	
	if(ucSerial.substring(0,8) == "_ceeprom")
	{
		Serial.println("Borrando EEPROM");
		disp.clreeprom();
		disp.reeprom();
		Serial.println("EEPROM ---> SRAM enviado;");
		cmdOk=1;
	}
	
	if(ucSerial.substring(0,6) == "_sndn[") //sndn[0,1]
	{
		RadioWriteTemp=ucSerial;
		Serial.println("_sndn enviando");

		cmdOk=1;
    TXradioEn=1;
	}

  if(ucSerial.substring(0,6) == "_rcvn[") //rcvn[0]
  {
    RadioWriteTemp=ucSerial;
    //Serial1.println("_rcvn enviando");

    cmdOk=1;
    TXradioEn=1;
  }
  
	
	if (cmdOk==0)
		Serial.println("Comando no identificado");
}

else
{
	TXradioEn=1;
	Serial1.println(ucSerial);
}
}
