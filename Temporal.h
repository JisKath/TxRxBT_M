void validarEnvio(String mensaje){
   int intentos=0;
   int okk=-1;
  while(okk==-1 && intentos<3)
  {
    okk = mensaje.indexOf("ok.");
    ++intentos;
    delay(50);
  }
  
  
}

void activarDispositivos(int _scn)
{
	if(escenario.Ambientes[_scn].habilitar== 2){
		for (int _Indice=0;_Indice<16;_Indice++){
			if(escenario.Ambientes[_scn].Dispositivos[_Indice].DispIndex !=0){
				internalData="_sndn[" + String(escenario.Ambientes[_scn].Dispositivos[_Indice].DispIndex) + "," ;
				internalData=internalData + String(escenario.Ambientes[_scn].Dispositivos[_Indice].Intensidad) + "]\n" ;
				fuenteCMD=4;
				Serial.println(internalData);
				ChkCMDinternal();
				delay(25);
				validarEnvio(internalResult);
				Serial.println(internalResult);
			}
		}
	}
}

void desactivarDispositivos(int _scn){
	if(escenario.Ambientes[_scn].habilitar== 4){
		for (int _Indice=0;_Indice<16;_Indice++){
			if(escenario.Ambientes[_scn].Dispositivos[_Indice].DispIndex !=0){
				internalData="_sndn[" + String(escenario.Ambientes[_scn].Dispositivos[_Indice].DispIndex) + "," ;
				internalData=internalData + "0]\n" ;
				fuenteCMD=4;
				Serial.println(internalData);
				ChkCMDinternal();
				delay(25);
				validarEnvio(internalResult);
				Serial.println(internalResult);
			}
		}
	}
}




void respaldarValores (int _scn)
{
	for (int _Indice=0;_Indice<16;_Indice++)
	{
			if ((escenario.Ambientes[_scn].Dispositivos[_Indice].DispIndex)!=0)
			{
				internalData="_rcvn[" + String(_Indice) + "]\n" ;
				fuenteCMD=4;
				ChkCMDinternal();
				delay(25);
				Serial.println(internalResult);
				Serial.println(internalResult.indexOf("Resp del Dispositivo:"));
				
			}
		
		

	}
	
}

void eventoVerificarn(int _n)                        // Verifica el status del evento n
{

  if(escenario.Ambientes[_n].habilitar== 1)
  {
    
    if(bitRead(escenario.Ambientes[_n].repetir,datetime.tm_wday))
    {
      internalData="_rSt0[" + String(_n) + "]\n" ;
      ChkCMDinternal();
      byte _hour=internalResult.substring(0).toInt();
      byte _separador=internalResult.indexOf(':')+1;
      byte _min=internalResult.substring(_separador).toInt();
      
      if(_hour <= datetime.tm_hour &&  _min <= datetime.tm_min)
      {
        escenario.Ambientes[_n].habilitar= 2;
        Serial.print("Evento ");
        Serial.print(_n);
        Serial.println(" corriendo...");
        activarDispositivos(_n);
		escenario.wSeeprom();
      }
    }
  }

  if(escenario.Ambientes[_n].habilitar== 2)
  {
    if(bitRead(escenario.Ambientes[_n].repetir,datetime.tm_wday))
    {
      internalData="_rSt1[" + String(_n) + "]\n" ;
      ChkCMDinternal();
      byte _hour1=internalResult.substring(0).toInt();
      byte _separador1=internalResult.indexOf(':')+1;
      byte _min1=internalResult.substring(_separador1).toInt();
      
      if(_hour1 <= datetime.tm_hour &&  _min1 <= datetime.tm_min)
      {
        escenario.Ambientes[_n].habilitar= 4;
        Serial.print("Evento ");
        Serial.print(_n);
        Serial.println(" finalizado...");
        desactivarDispositivos(_n);
		escenario.wSeeprom();
      }
    }   
    
  }

  if(escenario.Ambientes[_n].habilitar== 4)
  {
    if(bitRead(escenario.Ambientes[_n].repetir,datetime.tm_wday))
    {
      if( datetime.tm_hour == 0 && datetime.tm_min == 0)
      {
        escenario.Ambientes[_n].habilitar= 1;
        Serial.print("Evento ");
        Serial.print(_n);
        Serial.println(" reiniciado...");
        desactivarDispositivos(_n);
		escenario.wSeeprom();
      }
    }   
    
  }

}

void eventoVerificartodo(void)
{
	for (int _scn=0;_scn<16;_scn++)
	{
		eventoVerificarn(_scn);
	}
}
