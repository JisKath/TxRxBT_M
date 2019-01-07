void ChkCMDwf(void)												//Funcion para busqueda y ejecucion de comandos tipo _XXXX
{
if(wifiData.substring(0,1) == "_")
{
		
	cmdOk=0;
	wifiCmd2Snd=wifiData;

	if(wifiData.substring(0,6) == "_btoff")						//Comando para apagar modulo HC-05
	{	
		digitalWrite(BT_On, LOW);
		wifiString2Snd="Bluetooth Apagado;";
		cmdOk=1;
		fuenteCMD=13;
	}

	if(wifiData.substring(0,5) == "_bton")						//Comando para encender modulo HC-05
	{
		digitalWrite(BT_On, HIGH);
		wifiString2Snd="Bluetooth Encendido;";
		cmdOk=1;
	}

	if(wifiData.substring(0,5) == "_aton")						//Comando para encender Pin 34 en HC-05
	{
		digitalWrite(AT_Mode, HIGH);
		wifiString2Snd="Modo AT1 activo PIN 34;";
		cmdOk=1;
	}

	if(wifiData.substring(0,6) == "_atoff")						//Comando para apagar Pin 34 en HC-05
	{
		digitalWrite(AT_Mode, LOW);
		wifiString2Snd="Modo AT1 apagado;";
		cmdOk=1;
	}

	if(wifiData.substring(0,4) == "_wn[")
	{
		disp.wn(wifiData.substring(4).toInt(),wifiData.substring(wifiData.lastIndexOf(',')+1,wifiData.lastIndexOf(']')));
		wifiString2Snd="_wn OK;";
		cmdOk=1;
	}
		
	if(wifiData.substring(0,4) == "_rn[")
	{
		wifiEnviar(String(disp.Dispositivo[wifiData.substring(4).toInt()].nombre));
		wifiEnviar(" _rn OK;");
		cmdOk=1;
		fuenteCMD=13;
	}


	if(wifiData.substring(0,4) == "_wd[")
	{
		disp.wd(wifiData.substring(4).toInt(),wifiData.substring(wifiData.indexOf(',')+1,wifiData.lastIndexOf(']')));
		wifiString2Snd="_wd OK;";
		cmdOk=1;
	}

	if(wifiData.substring(0,4) == "_rd[")
	{
		wifiString2Snd=String(disp.Dispositivo[wifiData.substring(4).toInt()].direccion);
		wifiString2Snd=wifiString2Snd+" _rd OK;";
		cmdOk=1;
	}

	if(wifiData.substring(0,4) == "_rt[")
	{
		wifiString2Snd="_rt OK;";
		cmdOk=1;
	}
	
	if(wifiData.substring(0,5) == "_rall")
	{
		for (int i = 0 ; i < 16 ; i++)
		{

			Serial.print(i);
			Serial.print(" ");
			Serial.print(String(disp.Dispositivo[i].nombre));
			Serial.print(", ");
			Serial.print(String(disp.Dispositivo[i].direccion));
			Serial.println(" :");
		}
			
		Serial.println("_rall OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,8) == "_weeprom")
	{
		wifiString2Snd="enviando SRAM --> EEPROM";
		disp.weeprom();
		wifiString2Snd=wifiString2Snd+" SRAM --> EEPROM enviado;";
		cmdOk=1;
	}

	if(wifiData.substring(0,8) == "_reeprom")
	{
		wifiString2Snd="enviando EEPROM --> SRAM";
		disp.reeprom();
		wifiString2Snd=wifiString2Snd+"EEPROM ---> SRAM enviado;";
		cmdOk=1;
	}

	if(wifiData.substring(0,6) == "_sndn[") //sndn[0,1]
	{
		RadioWriteTemp=wifiData;
		//Serial.println("_sndn enviando");

		cmdOk=1;
		TXradioEn=1;
	}
	
	if(wifiData.substring(0,6) == "_rcvn[") //rcvn[0]
	{
		RadioWriteTemp=wifiData;
		//Serial.println("_rcvn enviando");

		cmdOk=1;
		TXradioEn=1;
	}

	if(wifiData.substring(0,6) == "_cpyd[") //cpyd[5,0]
	{
		String comando=""; 
		comando=wifiData;
		comando.remove(comando.indexOf(',')+1);
    int indice=0;
    indice=wifiData.substring((wifiData.indexOf(','))+1).toInt();
		comando.concat(disp.Dispositivo[indice].direccion);
    comando.concat("]");
    RadioWriteTemp=comando;

		cmdOk=1;
		TXradioEn=1;
	}
	
	if (cmdOk==0)
		wifiString2Snd="Comando no identificado;";


}

else
	Serial.println(wifiData);
}
