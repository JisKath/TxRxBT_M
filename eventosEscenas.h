void validarEnvio(String mensaje){

   int okk= mensaje.indexOf("ok.");;
  if(okk==-1 && intentoss<3 && EtapaValidarD)
  {
    ++intentoss;
    delay(50);
	
    Serial.print("Intento No. ");
    Serial.println(intentoss);
  }
  if(okk!=-1 || intentoss>=3)
  {
    intentoss=0;
	EtapaValidarD=false;
	Serial.println("Etapa de validacion Ok");
	}
}

void activarDispositivos(int _scn)
{
	if(escenario.Ambientes[_scn].habilitar== 2){
		if (_Indice<16){															//for (int _Indice=0;_Indice<16;_Indice++)
			if(escenario.Ambientes[_scn].Dispositivos[_Indice].DispIndex !=0 && EtapaActivarD )
			{
				EtapaValidarD=true;
				EtapaActivarD=true;
				internalData="_sndn[" + String(escenario.Ambientes[_scn].Dispositivos[_Indice].DispIndex) + "," ;
				internalData=internalData + String(escenario.Ambientes[_scn].Dispositivos[_Indice].Intensidad) + "]\n" ;
				fuenteCMD=4;
				Serial.println(internalData);
				ChkCMDinternal();
				delay(25);
				
				Serial.print("Activar Dispositivo ");
				Serial.println(_Indice);
			}
			
			bitWrite(EtapaActivando,_scn,true);
     
			validarEnvio(internalResult);
			Serial.println(internalResult);
			_Indice++;
		}
		if(_Indice>=16){
			_Indice=0;
			EtapaActivarD=false;
			EtapaBarrido=false;
			EtapaValidarD=false;
			bitWrite(EtapaActivando,_scn,false);
		}
	}
}

void desactivarDispositivos(int _scn){
	if(escenario.Ambientes[_scn].habilitar== 4){
		if (_Indice1<16){
			if(escenario.Ambientes[_scn].Dispositivos[_Indice1].DispIndex !=0 && EtapaDesactivarD)
			{
				EtapaValidarD=true;
				EtapaDesactivarD=true;
				internalData="_sndn[" + String(escenario.Ambientes[_scn].Dispositivos[_Indice1].DispIndex) + "," ;
				internalData=internalData + "0]\n" ;
				fuenteCMD=4;
				Serial.println(internalData);
				ChkCMDinternal();
				delay(25);
				Serial.print("Desactivar dispositivo ");
				Serial.println(_Indice1);
			}

			bitWrite(EtapaDesactivando,_scn,true);
			  
			validarEnvio(internalResult);
			Serial.println(internalResult);
			_Indice1++;
		}
		
		if(_Indice1>=16){
			_Indice1=0;
			EtapaDesactivarD=false;
			EtapaBarrido=false;
			EtapaValidarD=false;
			bitWrite(EtapaDesactivando,_scn,false);
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
//        Serial.println("_____________________");
//        Serial.println(_n);
//        Serial.println("Verificar n");
//        Serial.println(EtapaActivarD);
//        Serial.println(EtapaBarrido);
//        Serial.println(EtapaValidarD);
//        Serial.println(EtapaDesactivarD);        
//        Serial.println(EtapaActivando);        
//        Serial.println(EtapaDesactivando);        
//        Serial.println("_____________________");

//  if(escenario.Ambientes[_n].habilitar== 0)
//  {
//        escenario.Ambientes[_n].habilitar= 0;
//              _Indice1=0;
//      EtapaDesactivarD=false;
//      EtapaBarrido=false;
//      EtapaValidarD=false;
//      EtapaDesactivando=false;
//
//            _Indice=0;
//      EtapaActivarD=false;
//      EtapaBarrido=false;
//      EtapaValidarD=false;
//      EtapaActivando=false;
//      
//        Serial.print("Evento ");
//        Serial.print(_n);
//        Serial.println(" Deshabilitado...");
//    escenario.wSeeprom();
//    }   
    

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
        
  if(escenario.Ambientes[_n].habilitar== 1 || bitRead(EtapaActivando,_n))
	  
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
			EtapaActivarD=true;
			EtapaBarrido=true;
			Serial.print("Evento ");
			Serial.print(_n);
			Serial.println(" corriendo...");
			activarDispositivos(_n);
			escenario.wSeeprom();
		}
    }
  }

  if(escenario.Ambientes[_n].habilitar== 2 || bitRead(EtapaDesactivando,_n))
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
        
        EtapaActivarD=false;

		EtapaDesactivarD=true;
		EtapaBarrido=true;
		
        Serial.print("Evento ");
        Serial.print(_n);
        Serial.println(" finalizado...");
        desactivarDispositivos(_n);
		escenario.wSeeprom();
      }
    }   
    
  }



}

void eventoVerificartodo(void)
{
	eventoVerificarn(scn);

	if(scn<16 && !EtapaBarrido)												//Validar variable_scn 
	{
		scn++;

	}

	if(scn>=16)
	{
		scn=0;	
		
	}

}
