
void ChkCMD(void)												//Funcion para busqueda y ejecucion de comandos tipo _XXXX Puerto Serial
{
if(ucSerial.substring(0,1) == "_")
{
	cmdOk=0;


	if(ucSerial.substring(0,6) == "_btoff")						//Comando para apagar modulo HC-05
	{	
		digitalWrite(BT_On, LOW);
		Serial.println("Bluetooth Apagado;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,5) == "_bton")						//Comando para encender modulo HC-05
	{
		digitalWrite(BT_On, HIGH);
		Serial.println("Bluetooth Encendido;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,5) == "_aton")						//Comando para encender Pin 34 en HC-05
	{
		digitalWrite(AT_Mode, HIGH);
		Serial.println("Modo AT1 activo PIN 34;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,6) == "_atoff")						//Comando para apagar Pin 34 en HC-05
	{
		digitalWrite(AT_Mode, LOW);
		Serial.println("Modo AT1 apagado;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,4) == "_wn[")
	{
		disp.wn(ucSerial.substring(4).toInt(),ucSerial.substring(ucSerial.lastIndexOf(',')+1,ucSerial.lastIndexOf(']')));
		Serial.println("_wn OK;");
		cmdOk=1;
	}
		
	if(ucSerial.substring(0,4) == "_rn[")
	{
		Serial.println(String(disp.Dispositivo[ucSerial.substring(4).toInt()].nombre));
		Serial.println("_rn OK;");
		cmdOk=1;
	}


	if(ucSerial.substring(0,4) == "_wd[")
	{
		disp.wd(ucSerial.substring(4).toInt(),ucSerial.substring(ucSerial.indexOf(',')+1,ucSerial.lastIndexOf(']')));
		Serial.println("_wd OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,4) == "_rd[")
	{
		wifiEnviar(String(disp.Dispositivo[ucSerial.substring(4).toInt()].direccion));
		Serial.println("_rd OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,4) == "_rt[")
	{
		Serial.println("_rt OK;");
		cmdOk=1;
	}
	
	if(ucSerial.substring(0,5) == "_rall")
	{
  String temp=" ";
		for (int i = 0 ; i < 16 ; i++)
		{
			temp=(String(i));
			temp=temp+" ";
			temp=temp+(String(disp.Dispositivo[i].nombre));
			temp=temp+", ";
			temp=temp+(String(disp.Dispositivo[i].direccion));
			temp=temp+" :";
			Serial.println(temp);
		}
   
		Serial.println("_rall OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,8) == "_weeprom")
	{
		Serial.println("enviando SRAM --> EEPROM");
		disp.weeprom();
		Serial.println("SRAM --> EEPROM enviado;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,8) == "_reeprom")
	{
		Serial.println("enviando EEPROM --> SRAM");
		disp.reeprom();
		Serial.println("EEPROM ---> SRAM enviado;");
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
		//Serial.println("_sndn enviando");

		cmdOk=1;
		TXradioEn=1;
	}
	
	if(ucSerial.substring(0,6) == "_rcvn[") //rcvn[0]
	{
		RadioWriteTemp=ucSerial;
		//Serial.println("_rcvn enviando");

		cmdOk=1;
		TXradioEn=1;
	}

	if(ucSerial.substring(0,6) == "_cpyd[") //cpyd[5,0]
	{
		String comando=""; 
		comando=ucSerial;
		comando.remove(comando.indexOf(',')+1);
		int indice=0;
		indice=ucSerial.substring((ucSerial.indexOf(','))+1).toInt();
		comando.concat(disp.Dispositivo[indice].direccion);
		comando.concat("]");
		RadioWriteTemp=comando;

		cmdOk=1;
		TXradioEn=1;
	}
	
	if(ucSerial.substring(0,5) == "_wSn[")
	{
		escenario.wSn(ucSerial.substring(5).toInt(),ucSerial.substring(ucSerial.lastIndexOf(',')+1,ucSerial.lastIndexOf(']')));
		Serial.println("_wSn OK;");
		cmdOk=1;
	}
		
	if(ucSerial.substring(0,5) == "_rSn[")
	{
		Serial.println(String(escenario.Ambientes[ucSerial.substring(5).toInt()].nombre));
		Serial.println("_rSn OK;");
		cmdOk=1;
	}
	
	if(ucSerial.substring(0,6) == "_wSt0[")
	{
		escenario.wSt0(ucSerial.substring(6).toInt(),ucSerial.substring(ucSerial.lastIndexOf(',')+1,ucSerial.lastIndexOf(']')));
		Serial.println("_wSt0 OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,6) == "_rSt0[")
	{
		Serial.println(String(escenario.Ambientes[ucSerial.substring(6).toInt()].t0));
		Serial.println("_rSt0 OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,6) == "_wSt1[")
	{
		escenario.wSt1(ucSerial.substring(6).toInt(),ucSerial.substring(ucSerial.lastIndexOf(',')+1,ucSerial.lastIndexOf(']')));
		Serial.println("_wSt1 OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,6) == "_rSt1[")
	{
		Serial.println(String(escenario.Ambientes[ucSerial.substring(6).toInt()].t1));
		Serial.println("_rSt1 OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,7) == "_wSrep[")
	{
		escenario.Ambientes[ucSerial.substring(7).toInt()].repetir=ucSerial.substring(ucSerial.lastIndexOf(',')+1,ucSerial.lastIndexOf(']')).toInt();
		Serial.println("_wSrep OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,7) == "_rSrep[")
	{
		Serial.println(String(escenario.Ambientes[ucSerial.substring(7).toInt()].repetir,BIN));
		Serial.println("_rSrep OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,8) == "_wSrepa[")
	{
		escenario.Ambientes[ucSerial.substring(8).toInt()].repetirAlt=(byte)ucSerial.substring(ucSerial.lastIndexOf(',')+1,ucSerial.lastIndexOf(']')).toInt();
		Serial.println("_wSrepa OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,8) == "_rSrepa[")
	{
		Serial.println(String(escenario.Ambientes[ucSerial.substring(8).toInt()].repetirAlt,BIN));
		Serial.println("_rSrepa OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,6) == "_wSen[")
	{
		escenario.Ambientes[ucSerial.substring(6).toInt()].habilitar=(byte)ucSerial.substring(ucSerial.lastIndexOf(',')+1,ucSerial.lastIndexOf(']')).toInt();
		Serial.println("_wSen OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,6) == "_rSen[")
	{
		Serial.println(String(escenario.Ambientes[ucSerial.substring(6).toInt()].habilitar,BIN));
		Serial.println("_rSen OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,9) == "_wSeeprom")
	{
		Serial.println("enviando SRAM de Escenas --> EEPROM de Escenas");
		escenario.wSeeprom();
		Serial.println("SRAM de Escenas --> EEPROM de Escenas enviado;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,7) == "_wSdev[")
	{
		byte _Escn=ucSerial.substring(7).toInt();
		byte _comma1=ucSerial.indexOf(',')+1;
		byte _comma2=ucSerial.indexOf(',',_comma1)+1;
		byte _comma3=ucSerial.indexOf(',',_comma2)+1;
		
		byte _Indice=ucSerial.substring(_comma1).toInt();
		byte _disp=ucSerial.substring(_comma2).toInt();
		byte _Int=ucSerial.substring(_comma3).toInt();
		
		escenario.Ambientes[_Escn].Dispositivos[_Indice].DispIndex=_disp;
		escenario.Ambientes[_Escn].Dispositivos[_Indice].Intensidad=_Int;


		Serial.println("_wSdev OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,7) == "_rSdev[")
	{
		byte _Escn=ucSerial.substring(7).toInt();
		byte _comma1=ucSerial.indexOf(',')+1;
		
		byte _Indice=ucSerial.substring(_comma1).toInt();

		String _Temp="[" + String(_Indice) + ", " + String(escenario.Ambientes[_Escn].Dispositivos[_Indice].DispIndex) + ", " + String(escenario.Ambientes[_Escn].Dispositivos[_Indice].Intensidad)+"]";
		Serial.println(_Temp);
		
		//Serial.println(String(escenario.Ambientes[_Escn].Dispositivos[_Indice].DispIndex));
		//Serial.println(String(escenario.Ambientes[_Escn].Dispositivos[_Indice].Intensidad));

		Serial.println("_rSdev OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,7) == "_rSdall")
	{
		//byte _Escn=ucSerial.substring(8).toInt();
		int _Escn=0, idDisp=0;
		String _Temp="";
		
		for(_Escn=0;_Escn<16;_Escn++)
		{
			for(idDisp=0;idDisp<16;idDisp++)
			{
				_Temp= String(idDisp) + " " + escenario.Ambientes[_Escn].nombre + ", ";
				int i=escenario.Ambientes[_Escn].Dispositivos[idDisp].DispIndex;
				_Temp=_Temp + String(disp.Dispositivo[i].nombre) + ", ";
				_Temp=_Temp + String(escenario.Ambientes[_Escn].Dispositivos[idDisp].Intensidad) + " :";
				Serial.println(_Temp);
			}
		Serial.println("____________________");
		}
	
		Serial.println("_rSdall OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,7) == "_rSall[")
	{
		int _Escn=ucSerial.substring(7).toInt();
		int idDisp=0;
		String _Temp="";

		for(idDisp=0;idDisp<16;idDisp++)
		{
			_Temp= String(idDisp) + " " + escenario.Ambientes[_Escn].nombre + ", ";
			int i=escenario.Ambientes[_Escn].Dispositivos[idDisp].DispIndex;
			_Temp=_Temp + String(disp.Dispositivo[i].nombre) + ", ";
			_Temp=_Temp + String(escenario.Ambientes[_Escn].Dispositivos[idDisp].Intensidad) + " :";
			Serial.println(_Temp);
		}
		Serial.println("____________________");
	
		Serial.println("_rSall OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,6) == "_rSev[")
	{
		int _Escn=ucSerial.substring(6).toInt();
		String _Temp="";
		
		_Temp=String(_Escn) + " = " + escenario.Ambientes[_Escn].nombre + ">\n";
		_Temp=_Temp + "t0 = " + escenario.Ambientes[_Escn].t0 + ">\n";
		_Temp=_Temp + "t1 = " + escenario.Ambientes[_Escn].t1 + ">\n";
		_Temp=_Temp + "Dias = " + escenario.Ambientes[_Escn].repetir + ">\n";
		_Temp=_Temp + "TBD = " + escenario.Ambientes[_Escn].repetirAlt + ">\n";
		_Temp=_Temp + "Status = " + escenario.Ambientes[_Escn].habilitar + ">\n";
		Serial.println(_Temp);

		Serial.println("_rSev OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,9) == "_rSeeprom")
	{
		Serial.println("enviando EEPROM de Escenas --> SRAM de Escenas");
		escenario.rSeeprom();
		Serial.println("EEPROM de Escenas ---> SRAM de Escenas enviado;");
		cmdOk=1;
	}
	
	if(ucSerial.substring(0,9) == "_cSeeprom")
	{
		Serial.println("Borrando EEPROM de escenas");
		escenario.clrSeeprom();
		escenario.rSeeprom();
		Serial.println("EEPROM de escenas ---> SRAM de escenas enviado;");
		cmdOk=1;
	}
	
	if(ucSerial.substring(0,6) == "_testw") //Verifica Comunicacion WiFi
	{
		Serial.println("Ok...;");

		cmdOk=1;
	}
	


	if(ucSerial.substring(0,7) == "_wdate[")										//[WkD/MonthD/M/Y]
	{
		
		byte _dash1=ucSerial.indexOf('/')+1;
		byte _dash2=ucSerial.indexOf('/',_dash1)+1;
		byte _dash3=ucSerial.indexOf('/',_dash2)+1;
		
		datetime.tm_wday = ucSerial.substring(7).toInt();
		datetime.tm_mday = ucSerial.substring(_dash1).toInt();
		datetime.tm_mon = ucSerial.substring(_dash2).toInt();
		datetime.tm_year =timelib_y2k2tm(ucSerial.substring(_dash3).toInt());

		if (GFRTC.write(datetime)) {
			
			String _tempDate="";
			// write ok, print data sent to RTC
			_tempDate="Set date / time to: ";
			_tempDate=_tempDate + String(datetime.tm_hour);
			_tempDate=_tempDate + ':';
			_tempDate=_tempDate + String(datetime.tm_min);
			_tempDate=_tempDate + ':';
			_tempDate=_tempDate + String(datetime.tm_sec);
			_tempDate=_tempDate + ", Date (D/M/Y) = ";
			_tempDate=_tempDate + String(datetime.tm_mday);
			_tempDate=_tempDate + '/';
			_tempDate=_tempDate + String(datetime.tm_mon);
			_tempDate=_tempDate + '/';
			_tempDate=_tempDate + String(timelib_tm2y2k(datetime.tm_year));
			_tempDate=_tempDate + "\n";
			Serial.println(_tempDate);
			
		} else {
			// error reading the RTC
			Serial.println(F("Cannot write RTC."));
		}
		
		Serial.println("_wDate OK;");
		cmdOk=1;
	}
	
	if(ucSerial.substring(0,6) == "_rdate")										//(WkD/MonthD/M/Y)
	{

	// get date and time
	if (GFRTC.read(datetime)) {
		// read ok, print data from RTC
		String _tempDate="";
		_tempDate="[" + String(datetime.tm_wday) + "/";
		_tempDate=_tempDate + String(datetime.tm_mday) + "/";
		_tempDate=_tempDate + String(datetime.tm_mon) + "/";
		_tempDate=_tempDate + String(timelib_tm2y2k(datetime.tm_year)) + "]";
		
		Serial.println(_tempDate);
		
	} else {
		// error reading the RTC
		Serial.println("Cannot read RTC.");
	}
		
		Serial.println("_rDate OK;");
		cmdOk=1;
	}	

	if(ucSerial.substring(0,7) == "_wtime[")										//[hh:mm:ss]
	{
		
		byte _dash1=ucSerial.indexOf(':')+1;
		byte _dash2=ucSerial.indexOf(':',_dash1)+1;
				
		datetime.tm_hour = ucSerial.substring(7).toInt();
		datetime.tm_min = ucSerial.substring(_dash1).toInt();
		datetime.tm_sec = ucSerial.substring(_dash2).toInt();
		
		if (GFRTC.write(datetime)) {
			
			String _tempDate="";
			// write ok, print data sent to RTC
			_tempDate="Set date / time to: ";
			_tempDate=_tempDate + String(datetime.tm_hour);
			_tempDate=_tempDate + ':';
			_tempDate=_tempDate + String(datetime.tm_min);
			_tempDate=_tempDate + ':';
			_tempDate=_tempDate + String(datetime.tm_sec);
			_tempDate=_tempDate + ", Date (D/M/Y) = ";
			_tempDate=_tempDate + String(datetime.tm_mday);
			_tempDate=_tempDate + '/';
			_tempDate=_tempDate + String(datetime.tm_mon);
			_tempDate=_tempDate + '/';
			_tempDate=_tempDate + String(timelib_tm2y2k(datetime.tm_year));
			_tempDate=_tempDate + "\n";
			Serial.println(_tempDate);
			
		} else {
			// error reading the RTC
			Serial.println(F("Cannot write RTC."));
		}
		
		Serial.println("_wtime OK;");
		cmdOk=1;
	}

	if(ucSerial.substring(0,6) == "_rtime")										//[hh:mm:ss]
	{

	// get date and time
	if (GFRTC.read(datetime)) {
		// read ok, print data from RTC
		String _tempDate="";
		_tempDate="[" + String(datetime.tm_hour) + ":";
		_tempDate=_tempDate + String(datetime.tm_min) + ":";
		_tempDate=_tempDate + String(datetime.tm_sec) + "]";
		
		Serial.println(_tempDate);
		
	} else {
		// error reading the RTC
		Serial.println("Cannot read RTC.");
	}
		
		Serial.println("_rtime OK;");
		cmdOk=1;
	}	
	if (cmdOk==0)
		Serial.println("Comando no identificado;");
}

else
{
	TXradioEn=1;
	Serial1.println(ucSerial);
}
}


void ChkCMDbt(void)												//Funcion para busqueda y ejecucion de comandos tipo _XXXX Puerto BT
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
	
	if(btSerial.substring(0,8) == "_ceeprom")
	{
		Serial1.println("Borrando EEPROM");
		disp.clreeprom();
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


void ChkCMDwf(void)												//Funcion para busqueda y ejecucion de comandos tipo _XXXX Puerto WiFi
{
if(wifiData.substring(0,1) == "_")
{
		
	cmdOk=0;

	if(wifiData.substring(0,6) == "_btoff")						//Comando para apagar modulo HC-05
	{	
		digitalWrite(BT_On, LOW);
		wifiEnviarln("Bluetooth Apagado;");
		cmdOk=1;
	}

	if(wifiData.substring(0,5) == "_bton")						//Comando para encender modulo HC-05
	{
		digitalWrite(BT_On, HIGH);
		wifiEnviarln("Bluetooth Encendido;");
		cmdOk=1;
	}

	if(wifiData.substring(0,5) == "_aton")						//Comando para encender Pin 34 en HC-05
	{
		digitalWrite(AT_Mode, HIGH);
		wifiEnviarln("Modo AT1 activo PIN 34;");
		cmdOk=1;
	}

	if(wifiData.substring(0,6) == "_atoff")						//Comando para apagar Pin 34 en HC-05
	{
		digitalWrite(AT_Mode, LOW);
		wifiEnviarln("Modo AT1 apagado;");
		cmdOk=1;
	}

	if(wifiData.substring(0,4) == "_wn[")
	{
		disp.wn(wifiData.substring(4).toInt(),wifiData.substring(wifiData.lastIndexOf(',')+1,wifiData.lastIndexOf(']')));
		wifiEnviarln("_wn OK;");
		cmdOk=1;
	}
		
	if(wifiData.substring(0,4) == "_rn[")
	{
		wifiEnviarln(String(disp.Dispositivo[wifiData.substring(4).toInt()].nombre));
		wifiEnviarln("_rn OK;");
		cmdOk=1;
	}


	if(wifiData.substring(0,4) == "_wd[")
	{
		disp.wd(wifiData.substring(4).toInt(),wifiData.substring(wifiData.indexOf(',')+1,wifiData.lastIndexOf(']')));
		wifiEnviarln("_wd OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,4) == "_rd[")
	{
		wifiEnviar(String(disp.Dispositivo[wifiData.substring(4).toInt()].direccion));
		wifiEnviarln("_rd OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,4) == "_rt[")
	{
		wifiEnviarln("_rt OK;");
		cmdOk=1;
	}
	
	if(wifiData.substring(0,5) == "_rall")
	{
  String temp=" ";
		for (int i = 0 ; i < 16 ; i++)
		{
			temp=(String(i));
			temp=temp+" ";
			temp=temp+(String(disp.Dispositivo[i].nombre));
			temp=temp+", ";
			temp=temp+(String(disp.Dispositivo[i].direccion));
			temp=temp+" :";
			wifiEnviarln(temp);
		}
   
		wifiEnviarln("_rall OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,8) == "_weeprom")
	{
		wifiEnviarln("enviando SRAM --> EEPROM");
		disp.weeprom();
		wifiEnviarln("SRAM --> EEPROM enviado;");
		cmdOk=1;
	}

	if(wifiData.substring(0,8) == "_reeprom")
	{
		wifiEnviarln("enviando EEPROM --> SRAM");
		disp.reeprom();
		wifiEnviarln("EEPROM ---> SRAM enviado;");
		cmdOk=1;
	}

	if(wifiData.substring(0,8) == "_ceeprom")
	{
		wifiEnviarln("Borrando EEPROM");
		disp.clreeprom();
		disp.reeprom();
		wifiEnviarln("EEPROM ---> SRAM enviado;");
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
	
	if(wifiData.substring(0,5) == "_wSn[")
	{
		escenario.wSn(wifiData.substring(5).toInt(),wifiData.substring(wifiData.lastIndexOf(',')+1,wifiData.lastIndexOf(']')));
		wifiEnviarln("_wSn OK;");
		cmdOk=1;
	}
		
	if(wifiData.substring(0,5) == "_rSn[")
	{
		wifiEnviarln(String(escenario.Ambientes[wifiData.substring(5).toInt()].nombre));
		wifiEnviarln("_rSn OK;");
		cmdOk=1;
	}
	
	if(wifiData.substring(0,6) == "_wSt0[")
	{
		escenario.wSt0(wifiData.substring(6).toInt(),wifiData.substring(wifiData.lastIndexOf(',')+1,wifiData.lastIndexOf(']')));
		wifiEnviarln("_wSt0 OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,6) == "_rSt0[")
	{
		wifiEnviarln(String(escenario.Ambientes[wifiData.substring(6).toInt()].t0));
		wifiEnviarln("_rSt0 OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,6) == "_wSt1[")
	{
		escenario.wSt1(wifiData.substring(6).toInt(),wifiData.substring(wifiData.lastIndexOf(',')+1,wifiData.lastIndexOf(']')));
		wifiEnviarln("_wSt1 OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,6) == "_rSt1[")
	{
		wifiEnviarln(String(escenario.Ambientes[wifiData.substring(6).toInt()].t1));
		wifiEnviarln("_rSt1 OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,7) == "_wSrep[")
	{
		escenario.Ambientes[wifiData.substring(7).toInt()].repetir=wifiData.substring(wifiData.lastIndexOf(',')+1,wifiData.lastIndexOf(']')).toInt();
		wifiEnviarln("_wSrep OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,7) == "_rSrep[")
	{
		wifiEnviarln(String(escenario.Ambientes[wifiData.substring(7).toInt()].repetir,BIN));
		wifiEnviarln("_rSrep OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,8) == "_wSrepa[")
	{
		escenario.Ambientes[wifiData.substring(8).toInt()].repetirAlt=(byte)wifiData.substring(wifiData.lastIndexOf(',')+1,wifiData.lastIndexOf(']')).toInt();
		wifiEnviarln("_wSrepa OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,8) == "_rSrepa[")
	{
		wifiEnviarln(String(escenario.Ambientes[wifiData.substring(8).toInt()].repetirAlt,BIN));
		wifiEnviarln("_rSrepa OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,6) == "_wSen[")
	{
		escenario.Ambientes[wifiData.substring(6).toInt()].habilitar=(byte)wifiData.substring(wifiData.lastIndexOf(',')+1,wifiData.lastIndexOf(']')).toInt();
		wifiEnviarln("_wSen OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,6) == "_rSen[")
	{
		wifiEnviarln(String(escenario.Ambientes[wifiData.substring(6).toInt()].habilitar,BIN));
		wifiEnviarln("_rSen OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,9) == "_wSeeprom")
	{
		wifiEnviarln("enviando SRAM de Escenas --> EEPROM de Escenas");
		escenario.wSeeprom();
		wifiEnviarln("SRAM de Escenas --> EEPROM de Escenas enviado;");
		cmdOk=1;
	}

	if(wifiData.substring(0,7) == "_wSdev[")
	{
		byte _Escn=wifiData.substring(7).toInt();
		byte _comma1=wifiData.indexOf(',')+1;
		byte _comma2=wifiData.indexOf(',',_comma1)+1;
		byte _comma3=wifiData.indexOf(',',_comma2)+1;
		
		byte _Indice=wifiData.substring(_comma1).toInt();
		byte _disp=wifiData.substring(_comma2).toInt();
		byte _Int=wifiData.substring(_comma3).toInt();
		
		escenario.Ambientes[_Escn].Dispositivos[_Indice].DispIndex=_disp;
		escenario.Ambientes[_Escn].Dispositivos[_Indice].Intensidad=_Int;


		wifiEnviarln("_wSdev OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,7) == "_rSdev[")
	{
		byte _Escn=wifiData.substring(7).toInt();
		byte _comma1=wifiData.indexOf(',')+1;
		
		byte _Indice=wifiData.substring(_comma1).toInt();

		String _Temp="[" + String(_Indice) + ", " + String(escenario.Ambientes[_Escn].Dispositivos[_Indice].DispIndex) + ", " + String(escenario.Ambientes[_Escn].Dispositivos[_Indice].Intensidad)+"]";
		wifiEnviarln(_Temp);
		
		//wifiEnviarln(String(escenario.Ambientes[_Escn].Dispositivos[_Indice].DispIndex));
		//wifiEnviarln(String(escenario.Ambientes[_Escn].Dispositivos[_Indice].Intensidad));

		wifiEnviarln("_rSdev OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,7) == "_rSdall")
	{
		//byte _Escn=wifiData.substring(8).toInt();
		int _Escn=0, idDisp=0;
		String _Temp="";
		
		for(_Escn=0;_Escn<16;_Escn++)
		{
			for(idDisp=0;idDisp<16;idDisp++)
			{
				_Temp= String(idDisp) + " " + escenario.Ambientes[_Escn].nombre + ", ";
				int i=escenario.Ambientes[_Escn].Dispositivos[idDisp].DispIndex;
				_Temp=_Temp + String(disp.Dispositivo[i].nombre) + ", ";
				_Temp=_Temp + String(escenario.Ambientes[_Escn].Dispositivos[idDisp].Intensidad) + " :";
				wifiEnviarln(_Temp);
			}
		wifiEnviarln("____________________");
		}
	
		wifiEnviarln("_rSdall OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,7) == "_rSall[")
	{
		int _Escn=wifiData.substring(7).toInt();
		int idDisp=0;
		String _Temp="";

		for(idDisp=0;idDisp<16;idDisp++)
		{
			_Temp= String(idDisp) + " " + escenario.Ambientes[_Escn].nombre + ", ";
			int i=escenario.Ambientes[_Escn].Dispositivos[idDisp].DispIndex;
			_Temp=_Temp + String(disp.Dispositivo[i].nombre) + ", ";
			_Temp=_Temp + String(escenario.Ambientes[_Escn].Dispositivos[idDisp].Intensidad) + " :";
			wifiEnviarln(_Temp);
		}
		wifiEnviarln("____________________");
	
		wifiEnviarln("_rSall OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,6) == "_rSev[")
	{
		int _Escn=wifiData.substring(6).toInt();
		String _Temp="";
		
		_Temp=String(_Escn) + " = " + escenario.Ambientes[_Escn].nombre + ">\n";
		_Temp=_Temp + "t0 = " + escenario.Ambientes[_Escn].t0 + ">\n";
		_Temp=_Temp + "t1 = " + escenario.Ambientes[_Escn].t1 + ">\n";
		_Temp=_Temp + "Dias = " + escenario.Ambientes[_Escn].repetir + ">\n";
		_Temp=_Temp + "TBD = " + escenario.Ambientes[_Escn].repetirAlt + ">\n";
		_Temp=_Temp + "Status = " + escenario.Ambientes[_Escn].habilitar + ">\n";
		wifiEnviarln(_Temp);

		wifiEnviarln("_rSev OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,9) == "_rSeeprom")
	{
		wifiEnviarln("enviando EEPROM de Escenas --> SRAM de Escenas");
		escenario.rSeeprom();
		wifiEnviarln("EEPROM de Escenas ---> SRAM de Escenas enviado;");
		cmdOk=1;
	}
	
	if(wifiData.substring(0,9) == "_cSeeprom")
	{
		wifiEnviarln("Borrando EEPROM de escenas");
		escenario.clrSeeprom();
		escenario.rSeeprom();
		wifiEnviarln("EEPROM de escenas ---> SRAM de escenas enviado;");
		cmdOk=1;
	}
	
	if(wifiData.substring(0,6) == "_testw") //Verifica Comunicacion WiFi
	{
		wifiEnviarln("Ok...;");

		cmdOk=1;
	}

	if(wifiData.substring(0,7) == "_wdate[")										//[WkD/MonthD/M/Y]
	{
		
		byte _dash1=wifiData.indexOf('/')+1;
		byte _dash2=wifiData.indexOf('/',_dash1)+1;
		byte _dash3=wifiData.indexOf('/',_dash2)+1;
		
		datetime.tm_wday = wifiData.substring(7).toInt();
		datetime.tm_mday = wifiData.substring(_dash1).toInt();
		datetime.tm_mon = wifiData.substring(_dash2).toInt();
		datetime.tm_year =timelib_y2k2tm(wifiData.substring(_dash3).toInt());

		if (GFRTC.write(datetime)) {
			
			String _tempDate="";
			// write ok, print data sent to RTC
			_tempDate="Set date / time to: ";
			_tempDate=_tempDate + String(datetime.tm_hour);
			_tempDate=_tempDate + ':';
			_tempDate=_tempDate + String(datetime.tm_min);
			_tempDate=_tempDate + ':';
			_tempDate=_tempDate + String(datetime.tm_sec);
			_tempDate=_tempDate + ", Date (D/M/Y) = ";
			_tempDate=_tempDate + String(datetime.tm_mday);
			_tempDate=_tempDate + '/';
			_tempDate=_tempDate + String(datetime.tm_mon);
			_tempDate=_tempDate + '/';
			_tempDate=_tempDate + String(timelib_tm2y2k(datetime.tm_year));
			_tempDate=_tempDate + "\n";
			wifiEnviarln(_tempDate);
			
		} else {
			// error reading the RTC
			Serial.println(F("Cannot write RTC."));
		}
		
		wifiEnviarln("_wDate OK;");
		cmdOk=1;
	}
	
	if(wifiData.substring(0,6) == "_rdate")										//(WkD/MonthD/M/Y)
	{

	// get date and time
	if (GFRTC.read(datetime)) {
		// read ok, print data from RTC
		String _tempDate="";
		_tempDate="[" + String(datetime.tm_wday) + "/";
		_tempDate=_tempDate + String(datetime.tm_mday) + "/";
		_tempDate=_tempDate + String(datetime.tm_mon) + "/";
		_tempDate=_tempDate + String(timelib_tm2y2k(datetime.tm_year)) + "]";
		
		wifiEnviarln(_tempDate);
		
	} else {
		// error reading the RTC
		wifiEnviarln("Cannot read RTC.");
	}
		
		wifiEnviarln("_rDate OK;");
		cmdOk=1;
	}	

	if(wifiData.substring(0,7) == "_wtime[")										//[hh:mm:ss]
	{
		
		byte _dash1=wifiData.indexOf(':')+1;
		byte _dash2=wifiData.indexOf(':',_dash1)+1;
				
		datetime.tm_hour = wifiData.substring(7).toInt();
		datetime.tm_min = wifiData.substring(_dash1).toInt();
		datetime.tm_sec = wifiData.substring(_dash2).toInt();
		
		if (GFRTC.write(datetime)) {
			
			String _tempDate="";
			// write ok, print data sent to RTC
			_tempDate="Set date / time to: ";
			_tempDate=_tempDate + String(datetime.tm_hour);
			_tempDate=_tempDate + ':';
			_tempDate=_tempDate + String(datetime.tm_min);
			_tempDate=_tempDate + ':';
			_tempDate=_tempDate + String(datetime.tm_sec);
			_tempDate=_tempDate + ", Date (D/M/Y) = ";
			_tempDate=_tempDate + String(datetime.tm_mday);
			_tempDate=_tempDate + '/';
			_tempDate=_tempDate + String(datetime.tm_mon);
			_tempDate=_tempDate + '/';
			_tempDate=_tempDate + String(timelib_tm2y2k(datetime.tm_year));
			_tempDate=_tempDate + "\n";
			wifiEnviarln(_tempDate);
			
		} else {
			// error reading the RTC
			Serial.println(F("Cannot write RTC."));
		}
		
		wifiEnviarln("_wtime OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,6) == "_rtime")										//[hh:mm:ss]
	{

	// get date and time
	if (GFRTC.read(datetime)) {
		// read ok, print data from RTC
		String _tempDate="";
		_tempDate="[" + String(datetime.tm_hour) + ":";
		_tempDate=_tempDate + String(datetime.tm_min) + ":";
		_tempDate=_tempDate + String(datetime.tm_sec) + "]";
		
		wifiEnviarln(_tempDate);
		
	} else {
		// error reading the RTC
		wifiEnviarln("Cannot read RTC.");
	}
		
		wifiEnviarln("_rtime OK;");
		cmdOk=1;
	}

	if(wifiData.substring(0,4) == "_???")										//Comandos de ayuda
	{
		// wifiEnviarln("Lista de comandos: ");
		// wifiEnviarln("_wn[xx,yyyy] --> Asignar nombre yyyy al dispositivo xx; donde 0<= xx <=15 ");
		// wifiEnviarln("_rn[xx] --> Leer nombre del dispositivo xx; donde 0<= xx <=15  ");
		// wifiEnviarln("_wd[xx,yy@yy] --> Asignar direccion yy@yy al dispositivo xx; donde 0<= xx <=15  y 0<= yy <=99");
		// wifiEnviarln("_rd[xx] --> Leer direccion del dispositivo xx; donde 0<= xx <=15  ");
		// wifiEnviarln("_rall --> Ver todos los dispositivos");
		// wifiEnviarln("_weeprom --> Escribir datos de la RAM a la EEPROM");
		// wifiEnviarln("_reeprom --> Leer datos de la EEPROM a la RAM");
		// wifiEnviarln("_ceeprom --> borrar datos de la EEPROM");
		// wifiEnviarln("_sndn[xx,yyy] --> Enviar intensidad de luz yyy al dispositivo xx; donde 0%<= yyy <=100% ");
		// wifiEnviarln("_rcvn[xx] --> Leer intensidad de luz del dispositivo xx; donde 0%<= yyy <=100% ");
		// wifiEnviarln("_cpyd[xx,yy] --> Asignar direccion del dispositivo yy al dispositivo xx ");
		// wifiEnviarln("_wSn[xx,yyyy] --> Asignar nombre yyyy a la escena xx; donde 0<= xx <=15 ");
		// wifiEnviarln("_rSn[xx] --> Leer nombre de la escena xx; donde 0<= xx <=15  ");
		// wifiEnviarln("_wSt0[xx,hh:mm] --> Asignar hora de inicio hh:mm a la escena xx; donde 0<= xx <=15 ");
		// wifiEnviarln("_rSt0[xx] --> Leer hora de inicio de la escena xx; donde 0<= xx <=15 ");
		// wifiEnviarln("_wSt1[xx,hh:mm] --> Asignar hora de fin hh:mm a la escena xx; donde 0<= xx <=15 ");
		// wifiEnviarln("_rSt1[xx] --> Leer hora de fin de la escena xx; donde 0<= xx <=15 ");
		// wifiEnviarln("_wSrep[xx,yyy] --> Asignar dias yyy donde la escena xx se habilitara; donde yyy.0 --> domingo ... yyy.7 --> sabado ");
		// wifiEnviarln("_rSrep[xx] --> Leer los dias donde la escena xx se habilitara; donde yyy.0 --> domingo ... yyy.7 --> sabado ");

		wifiEnviarln("_??? OK;");
		cmdOk=1;
	}

	if (cmdOk==0)
		wifiEnviarln("Comando no identificado;");


}
else
	Serial.println(wifiData);
}


void ChkCMDinternal(void)										//Funcion para busqueda y ejecucion de comandos tipo _XXXX Interno uC
{
if(internalData.substring(0,1) == "_")
{
	internalResult="";	
	cmdOk=0;

	if(internalData.substring(0,6) == "_btoff")						//Comando para apagar modulo HC-05
	{	
		digitalWrite(BT_On, LOW);
		Serial.println("Bluetooth Apagado;");
		cmdOk=1;
	}

	if(internalData.substring(0,5) == "_bton")						//Comando para encender modulo HC-05
	{
		digitalWrite(BT_On, HIGH);
		Serial.println("Bluetooth Encendido;");
		cmdOk=1;
	}

	if(internalData.substring(0,5) == "_aton")						//Comando para encender Pin 34 en HC-05
	{
		digitalWrite(AT_Mode, HIGH);
		Serial.println("Modo AT1 activo PIN 34;");
		cmdOk=1;
	}

	if(internalData.substring(0,6) == "_atoff")						//Comando para apagar Pin 34 en HC-05
	{
		digitalWrite(AT_Mode, LOW);
		Serial.println("Modo AT1 apagado;");
		cmdOk=1;
	}

	if(internalData.substring(0,4) == "_wn[")
	{
		disp.wn(internalData.substring(4).toInt(),internalData.substring(internalData.lastIndexOf(',')+1,internalData.lastIndexOf(']')));
		Serial.println("_wn OK;");
		cmdOk=1;
	}
		
	if(internalData.substring(0,4) == "_rn[")
	{
		Serial.println(String(disp.Dispositivo[internalData.substring(4).toInt()].nombre));
		Serial.println("_rn OK;");
		cmdOk=1;
	}


	if(internalData.substring(0,4) == "_wd[")
	{
		disp.wd(internalData.substring(4).toInt(),internalData.substring(internalData.indexOf(',')+1,internalData.lastIndexOf(']')));
		Serial.println("_wd OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,4) == "_rd[")
	{
		wifiEnviar(String(disp.Dispositivo[internalData.substring(4).toInt()].direccion));
		Serial.println("_rd OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,4) == "_rt[")
	{
		Serial.println("_rt OK;");
		cmdOk=1;
	}
	
	if(internalData.substring(0,5) == "_rall")
	{
  String temp=" ";
		for (int i = 0 ; i < 16 ; i++)
		{
			temp=(String(i));
			temp=temp+" ";
			temp=temp+(String(disp.Dispositivo[i].nombre));
			temp=temp+", ";
			temp=temp+(String(disp.Dispositivo[i].direccion));
			temp=temp+" :";
			Serial.println(temp);
		}
   
		Serial.println("_rall OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,8) == "_weeprom")
	{
		Serial.println("enviando SRAM --> EEPROM");
		disp.weeprom();
		Serial.println("SRAM --> EEPROM enviado;");
		cmdOk=1;
	}

	if(internalData.substring(0,8) == "_reeprom")
	{
		Serial.println("enviando EEPROM --> SRAM");
		disp.reeprom();
		Serial.println("EEPROM ---> SRAM enviado;");
		cmdOk=1;
	}

	if(internalData.substring(0,8) == "_ceeprom")
	{
		Serial.println("Borrando EEPROM");
		disp.clreeprom();
		disp.reeprom();
		Serial.println("EEPROM ---> SRAM enviado;");
		cmdOk=1;
	}
	
	if(internalData.substring(0,6) == "_sndn[") //sndn[0,1]
	{
		RadioWriteTemp=internalData;
		//Serial.println("_sndn enviando");

		cmdOk=1;
		TXradioEn=1;
	}
	
	if(internalData.substring(0,6) == "_rcvn[") //rcvn[0]
	{
		RadioWriteTemp=internalData;
		//Serial.println("_rcvn enviando");

		cmdOk=1;
		TXradioEn=1;
	}

	if(internalData.substring(0,6) == "_cpyd[") //cpyd[5,0]
	{
		String comando=""; 
		comando=internalData;
		comando.remove(comando.indexOf(',')+1);
		int indice=0;
		indice=internalData.substring((internalData.indexOf(','))+1).toInt();
		comando.concat(disp.Dispositivo[indice].direccion);
		comando.concat("]");
		RadioWriteTemp=comando;

		cmdOk=1;
		TXradioEn=1;
	}
	
	if(internalData.substring(0,5) == "_wSn[")
	{
		escenario.wSn(internalData.substring(5).toInt(),internalData.substring(internalData.lastIndexOf(',')+1,internalData.lastIndexOf(']')));
		Serial.println("_wSn OK;");
		cmdOk=1;
	}
		
	if(internalData.substring(0,5) == "_rSn[")
	{
		Serial.println(String(escenario.Ambientes[internalData.substring(5).toInt()].nombre));
		Serial.println("_rSn OK;");
		cmdOk=1;
	}
	
	if(internalData.substring(0,6) == "_wSt0[")
	{
		escenario.wSt0(internalData.substring(6).toInt(),internalData.substring(internalData.lastIndexOf(',')+1,internalData.lastIndexOf(']')));
		Serial.println("_wSt0 OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,6) == "_rSt0[")
	{
		//Serial.println(String(escenario.Ambientes[internalData.substring(6).toInt()].t0));
		internalResult=String(escenario.Ambientes[internalData.substring(6).toInt()].t0);
		//Serial.println("_rSt0 OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,6) == "_wSt1[")
	{
		escenario.wSt1(internalData.substring(6).toInt(),internalData.substring(internalData.lastIndexOf(',')+1,internalData.lastIndexOf(']')));
		Serial.println("_wSt1 OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,6) == "_rSt1[")
	{
		//Serial.println(String(escenario.Ambientes[internalData.substring(6).toInt()].t1));
		internalResult=String(escenario.Ambientes[internalData.substring(6).toInt()].t1);
		//Serial.println("_rSt1 OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,7) == "_wSrep[")
	{
		escenario.Ambientes[internalData.substring(7).toInt()].repetir=internalData.substring(internalData.lastIndexOf(',')+1,internalData.lastIndexOf(']')).toInt();
		Serial.println("_wSrep OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,7) == "_rSrep[")
	{
		Serial.println(String(escenario.Ambientes[internalData.substring(7).toInt()].repetir,BIN));
		Serial.println("_rSrep OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,8) == "_wSrepa[")
	{
		escenario.Ambientes[internalData.substring(8).toInt()].repetirAlt=(byte)internalData.substring(internalData.lastIndexOf(',')+1,internalData.lastIndexOf(']')).toInt();
		Serial.println("_wSrepa OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,8) == "_rSrepa[")
	{
		Serial.println(String(escenario.Ambientes[internalData.substring(8).toInt()].repetirAlt,BIN));
		Serial.println("_rSrepa OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,6) == "_wSen[")
	{
		escenario.Ambientes[internalData.substring(6).toInt()].habilitar=(byte)internalData.substring(internalData.lastIndexOf(',')+1,internalData.lastIndexOf(']')).toInt();
		Serial.println("_wSen OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,6) == "_rSen[")
	{
		Serial.println(String(escenario.Ambientes[internalData.substring(6).toInt()].habilitar,BIN));
		Serial.println("_rSen OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,9) == "_wSeeprom")
	{
		Serial.println("enviando SRAM de Escenas --> EEPROM de Escenas");
		escenario.wSeeprom();
		Serial.println("SRAM de Escenas --> EEPROM de Escenas enviado;");
		cmdOk=1;
	}

	if(internalData.substring(0,7) == "_wSdev[")
	{
		byte _Escn=internalData.substring(7).toInt();
		byte _comma1=internalData.indexOf(',')+1;
		byte _comma2=internalData.indexOf(',',_comma1)+1;
		byte _comma3=internalData.indexOf(',',_comma2)+1;
		
		byte _Indice=internalData.substring(_comma1).toInt();
		byte _disp=internalData.substring(_comma2).toInt();
		byte _Int=internalData.substring(_comma3).toInt();
		
		escenario.Ambientes[_Escn].Dispositivos[_Indice].DispIndex=_disp;
		escenario.Ambientes[_Escn].Dispositivos[_Indice].Intensidad=_Int;


		Serial.println("_wSdev OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,7) == "_rSdev[")
	{
		byte _Escn=internalData.substring(7).toInt();
		byte _comma1=internalData.indexOf(',')+1;
		
		byte _Indice=internalData.substring(_comma1).toInt();

		String _Temp="[" + String(_Indice) + ", " + String(escenario.Ambientes[_Escn].Dispositivos[_Indice].DispIndex) + ", " + String(escenario.Ambientes[_Escn].Dispositivos[_Indice].Intensidad)+"]";
		Serial.println(_Temp);
		
		//Serial.println(String(escenario.Ambientes[_Escn].Dispositivos[_Indice].DispIndex));
		//Serial.println(String(escenario.Ambientes[_Escn].Dispositivos[_Indice].Intensidad));

		Serial.println("_rSdev OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,7) == "_rSdall")
	{
		//byte _Escn=internalData.substring(8).toInt();
		int _Escn=0, idDisp=0;
		String _Temp="";
		
		for(_Escn=0;_Escn<16;_Escn++)
		{
			for(idDisp=0;idDisp<16;idDisp++)
			{
				_Temp= String(idDisp) + " " + escenario.Ambientes[_Escn].nombre + ", ";
				int i=escenario.Ambientes[_Escn].Dispositivos[idDisp].DispIndex;
				_Temp=_Temp + String(disp.Dispositivo[i].nombre) + ", ";
				_Temp=_Temp + String(escenario.Ambientes[_Escn].Dispositivos[idDisp].Intensidad) + " :";
				Serial.println(_Temp);
			}
		Serial.println("____________________");
		}
	
		Serial.println("_rSdall OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,7) == "_rSall[")
	{
		int _Escn=internalData.substring(7).toInt();
		int idDisp=0;
		String _Temp="";

		for(idDisp=0;idDisp<16;idDisp++)
		{
			_Temp= String(idDisp) + " " + escenario.Ambientes[_Escn].nombre + ", ";
			int i=escenario.Ambientes[_Escn].Dispositivos[idDisp].DispIndex;
			_Temp=_Temp + String(disp.Dispositivo[i].nombre) + ", ";
			_Temp=_Temp + String(escenario.Ambientes[_Escn].Dispositivos[idDisp].Intensidad) + " :";
			Serial.println(_Temp);
		}
		Serial.println("____________________");
	
		Serial.println("_rSall OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,6) == "_rSev[")
	{
		int _Escn=internalData.substring(6).toInt();
		String _Temp="";
		
		_Temp=String(_Escn) + " = " + escenario.Ambientes[_Escn].nombre + ">\n";
		_Temp=_Temp + "t0 = " + escenario.Ambientes[_Escn].t0 + ">\n";
		_Temp=_Temp + "t1 = " + escenario.Ambientes[_Escn].t1 + ">\n";
		_Temp=_Temp + "Dias = " + escenario.Ambientes[_Escn].repetir + ">\n";
		_Temp=_Temp + "TBD = " + escenario.Ambientes[_Escn].repetirAlt + ">\n";
		_Temp=_Temp + "Status = " + escenario.Ambientes[_Escn].habilitar + ">\n";
		Serial.println(_Temp);

		Serial.println("_rSev OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,9) == "_rSeeprom")
	{
		Serial.println("enviando EEPROM de Escenas --> SRAM de Escenas");
		escenario.rSeeprom();
		Serial.println("EEPROM de Escenas ---> SRAM de Escenas enviado;");
		cmdOk=1;
	}
	
	if(internalData.substring(0,9) == "_cSeeprom")
	{
		Serial.println("Borrando EEPROM de escenas");
		escenario.clrSeeprom();
		escenario.rSeeprom();
		Serial.println("EEPROM de escenas ---> SRAM de escenas enviado;");
		cmdOk=1;
	}
	
	if(internalData.substring(0,6) == "_testw") //Verifica Comunicacion WiFi
	{
		Serial.println("Ok...;");

		cmdOk=1;
	}
	


	if(internalData.substring(0,7) == "_wdate[")										//[WkD/MonthD/M/Y]
	{
		
		byte _dash1=internalData.indexOf('/')+1;
		byte _dash2=internalData.indexOf('/',_dash1)+1;
		byte _dash3=internalData.indexOf('/',_dash2)+1;
		
		datetime.tm_wday = internalData.substring(7).toInt();
		datetime.tm_mday = internalData.substring(_dash1).toInt();
		datetime.tm_mon = internalData.substring(_dash2).toInt();
		datetime.tm_year =timelib_y2k2tm(internalData.substring(_dash3).toInt());

		if (GFRTC.write(datetime)) {
			
			String _tempDate="";
			// write ok, print data sent to RTC
			_tempDate="Set date / time to: ";
			_tempDate=_tempDate + String(datetime.tm_hour);
			_tempDate=_tempDate + ':';
			_tempDate=_tempDate + String(datetime.tm_min);
			_tempDate=_tempDate + ':';
			_tempDate=_tempDate + String(datetime.tm_sec);
			_tempDate=_tempDate + ", Date (D/M/Y) = ";
			_tempDate=_tempDate + String(datetime.tm_mday);
			_tempDate=_tempDate + '/';
			_tempDate=_tempDate + String(datetime.tm_mon);
			_tempDate=_tempDate + '/';
			_tempDate=_tempDate + String(timelib_tm2y2k(datetime.tm_year));
			_tempDate=_tempDate + "\n";
			Serial.println(_tempDate);
			
		} else {
			// error reading the RTC
			Serial.println(F("Cannot write RTC."));
		}
		
		Serial.println("_wDate OK;");
		cmdOk=1;
	}
	
	if(internalData.substring(0,6) == "_rdate")										//(WkD/MonthD/M/Y)
	{

	// get date and time
	if (GFRTC.read(datetime)) {
		// read ok, print data from RTC
		String _tempDate="";
		_tempDate="[" + String(datetime.tm_wday) + "/";
		_tempDate=_tempDate + String(datetime.tm_mday) + "/";
		_tempDate=_tempDate + String(datetime.tm_mon) + "/";
		_tempDate=_tempDate + String(timelib_tm2y2k(datetime.tm_year)) + "]";
		
		Serial.println(_tempDate);
		
	} else {
		// error reading the RTC
		Serial.println("Cannot read RTC.");
	}
		
		Serial.println("_rDate OK;");
		cmdOk=1;
	}	

	if(internalData.substring(0,7) == "_wtime[")										//[hh:mm:ss]
	{
		
		byte _dash1=internalData.indexOf(':')+1;
		byte _dash2=internalData.indexOf(':',_dash1)+1;
				
		datetime.tm_hour = internalData.substring(7).toInt();
		datetime.tm_min = internalData.substring(_dash1).toInt();
		datetime.tm_sec = internalData.substring(_dash2).toInt();
		
		if (GFRTC.write(datetime)) {
			
			String _tempDate="";
			// write ok, print data sent to RTC
			_tempDate="Set date / time to: ";
			_tempDate=_tempDate + String(datetime.tm_hour);
			_tempDate=_tempDate + ':';
			_tempDate=_tempDate + String(datetime.tm_min);
			_tempDate=_tempDate + ':';
			_tempDate=_tempDate + String(datetime.tm_sec);
			_tempDate=_tempDate + ", Date (D/M/Y) = ";
			_tempDate=_tempDate + String(datetime.tm_mday);
			_tempDate=_tempDate + '/';
			_tempDate=_tempDate + String(datetime.tm_mon);
			_tempDate=_tempDate + '/';
			_tempDate=_tempDate + String(timelib_tm2y2k(datetime.tm_year));
			_tempDate=_tempDate + "\n";
			Serial.println(_tempDate);
			
		} else {
			// error reading the RTC
			Serial.println(F("Cannot write RTC."));
		}
		
		Serial.println("_wtime OK;");
		cmdOk=1;
	}

	if(internalData.substring(0,6) == "_rtime")										//[hh:mm:ss]
	{

	// get date and time
	if (GFRTC.read(datetime)) {
		// read ok, print data from RTC
		String _tempDate="";
		_tempDate="[" + String(datetime.tm_hour) + ":";
		_tempDate=_tempDate + String(datetime.tm_min) + ":";
		_tempDate=_tempDate + String(datetime.tm_sec) + "]";
		internalResult=_tempDate;
		Serial.println(_tempDate);
		
	} else {
		// error reading the RTC
		Serial.println("Cannot read RTC.");
	}
		
		Serial.println("_rtime OK;");
		cmdOk=1;
	}

	if (cmdOk==0)
		Serial.println("Comando no identificado;");

internalData="";
}
else
	Serial.println(internalData);
}
