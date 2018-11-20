
void ChkCMDbt(void)												//Funcion para busqueda y ejecucion de comandos tipo _XXXX
{
if(btSerial.substring(0,1) == "_")
{
		
	cmdOk=0;

	if(btSerial.substring(0,6) == "_btoff")						//Comando para apagar modulo HC-05
	{	
		digitalWrite(BT_On, LOW);
		Serial1.println("Bluetooth Apagado;");
		cmdOk=1;
	}

	if(btSerial.substring(0,5) == "_bton")						//Comando para encender modulo HC-05
	{
		digitalWrite(BT_On, HIGH);
		Serial1.println("Bluetooth Encendido;");
		cmdOk=1;
	}

	if(btSerial.substring(0,5) == "_aton")						//Comando para encender Pin 34 en HC-05
	{
		digitalWrite(AT_Mode, HIGH);
		Serial1.println("Modo AT1 activo PIN 34;");
		cmdOk=1;
	}

	if(btSerial.substring(0,6) == "_atoff")						//Comando para apagar Pin 34 en HC-05
	{
		digitalWrite(AT_Mode, LOW);
		Serial1.println("Modo AT1 apagado;");
		cmdOk=1;
	}

	if(btSerial.substring(0,4) == "_wn[")
	{
		disp.wn(btSerial.substring(4).toInt(),btSerial.substring(btSerial.lastIndexOf(',')+1,btSerial.lastIndexOf(']')));
		Serial1.println("_wn OK;");
		cmdOk=1;
	}
		
	if(btSerial.substring(0,4) == "_rn[")
	{
		Serial1.println(String(disp.Dispositivo[btSerial.substring(4).toInt()].nombre));
		Serial1.println("_rn OK;");
		cmdOk=1;
	}


	if(btSerial.substring(0,4) == "_wd[")
	{
		disp.wd(btSerial.substring(4).toInt(),btSerial.substring(btSerial.indexOf(',')+1,btSerial.lastIndexOf(']')));
		Serial1.println("_wd OK;");
		cmdOk=1;
	}

	if(btSerial.substring(0,4) == "_rd[")
	{
		Serial1.println(String(disp.Dispositivo[btSerial.substring(4).toInt()].direccion));
		Serial1.print("_rd OK;");
		cmdOk=1;
	}

	if(btSerial.substring(0,4) == "_rt[")
	{
		Serial1.print("_rt OK;");
		cmdOk=1;
	}
	
	if(btSerial.substring(0,5) == "_rall")
	{
		for (int i = 0 ; i < 16 ; i++)
		{

			Serial1.print(i);
			Serial1.print(" ");
			Serial1.print(String(disp.Dispositivo[i].nombre));
			Serial1.print(", ");
			Serial1.print(String(disp.Dispositivo[i].direccion));
			Serial1.println(" :");
		}
			
		Serial1.println("_rall OK;");
		cmdOk=1;
	}

	if(btSerial.substring(0,8) == "_weeprom")
	{
		Serial1.println("enviando SRAM --> EEPROM");
		disp.weeprom();
		Serial1.println("SRAM --> EEPROM enviado;");
		cmdOk=1;
	}

	if(btSerial.substring(0,8) == "_reeprom")
	{
		Serial1.println("enviando EEPROM --> SRAM");
		disp.reeprom();
		Serial1.println("EEPROM ---> SRAM enviado;");
		cmdOk=1;
	}

	if(btSerial.substring(0,6) == "_sndn[") //sndn[0,1]
	{
		RadioWriteTemp=btSerial;
		//Serial1.println("_sndn enviando");

		cmdOk=1;
		TXradioEn=1;
	}
	
	if(btSerial.substring(0,6) == "_rcvn[") //rcvn[0]
	{
		RadioWriteTemp=btSerial;
		//Serial1.println("_rcvn enviando");

		cmdOk=1;
		TXradioEn=1;
	}

	if(btSerial.substring(0,6) == "_cpyd[") //cpyd[5,0]
	{
		String comando=""; 
		comando=btSerial;
		comando.remove(comando.indexOf(',')+1);
    int indice=0;
    indice=btSerial.substring((btSerial.indexOf(','))+1).toInt();
		comando.concat(disp.Dispositivo[indice].direccion);
    comando.concat("]");
    RadioWriteTemp=comando;

		cmdOk=1;
		TXradioEn=1;
	}
	
	if (cmdOk==0)
		Serial1.println("Comando no identificado;");


}

else
	Serial1.println(btSerial);
}
