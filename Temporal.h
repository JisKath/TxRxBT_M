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
	
	if (cmdOk==0)
		wifiEnviarln("Comando no identificado;");
