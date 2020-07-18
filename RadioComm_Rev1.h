
String selectPipe(String _pipe)
{
  String ix="0";
  ix=ix + _pipe.substring(0,2);
  return(ix); 
}

String selectPipeL(String _pipe)
{
  String ix="0";
  ix=ix + _pipe.substring(3,5);
  return(ix);

}

String RadioRead(void)
{
  String Mensaje;
  Mensaje.reserve(16);
  Mensaje.remove(0, 15);
  
  while(RF.available())
	Mensaje=RF.readString();

  return (Mensaje);
}

bool RadioWrite(String theMessage)
{
  bool a=false;

  HC11.sends(theMessage);
  a=true;
  
  return (a);
}

void Duplex2Radio(int Enable)
{
	if(Enable==1)
	{
		HC11.ATmode(true);
		HC11.Addr(selectPipe(disp.Dispositivo[RadioWriteTemp.substring(6).toInt()].direccion));
		HC11.Canal(selectPipeL(disp.Dispositivo[RadioWriteTemp.substring(6).toInt()].direccion));
		HC11.ATmode(false);
		
		delay(10);
		
		if(fuenteCMD==1){
			Serial.print("Enviando  ");
			Serial.println(RadioWriteTemp);
		}
		
		if(fuenteCMD==2){
			Serial1.print("Enviando  ");
			Serial1.println(RadioWriteTemp);
		}
		
		if(fuenteCMD==3){
			wifiEnviar("Enviando  ");
			wifiEnviarln(RadioWriteTemp);
		}

		if(fuenteCMD==4){
			Serial.print("Enviando  ");
			Serial.println(RadioWriteTemp);
		}
		
		bool ok = false;
		int TXattempts=0;
		while(!ok && TXattempts<3)
		{
			ok = RadioWrite(RadioWriteTemp);
			++TXattempts;
			delay(100);
		}
		
		if(fuenteCMD==1){
			Serial.print("Intentos: ");
			Serial.println(TXattempts);
		}
		
		if(fuenteCMD==2){
			Serial1.print("Intentos: ");
			Serial1.println(TXattempts);
		}
		
		if(fuenteCMD==3){
			wifiEnviar("Intentos: ");
			wifiEnviarln(String(TXattempts));
		}

		if(fuenteCMD==4){
			Serial.print("Intentos: ");
			Serial.println(TXattempts);
		}
		
		if (ok){
			if(fuenteCMD==1)
				Serial.println("Envio satisfactorio");

			if(fuenteCMD==2)
				Serial1.println("Envio satisfactorio");
			
			if(fuenteCMD==3)
				wifiEnviarln("Envio satisfactorio");
			
			if(fuenteCMD==4)
				Serial.println("Envio satisfactorio");
		}
		
		else{
			if(fuenteCMD==1)
				Serial.println("Falla al transmitir");
			
			if(fuenteCMD==2)
				Serial1.println("Falla al transmitir");
			
			if(fuenteCMD==3)
				wifiEnviarln("Falla al transmitir");

			if(fuenteCMD==4)
				Serial.println("Falla al transmitir");
		}
		
		cmdOk=0;
		TXradioEn=0;
		
	}
	
}

void ActualizarEdos(void)
{
	if(sweepDev>=16)
	{
		sweepDev=0;
		firstScan=false;
	}
	
	if(sweepDev<16)
	{
        //Serial.print("revisando ");
        //Serial.println(sweepInt);
        sweepInt++;

        if(sweepInt>5)
        {
          rcvn_Ok=true;
          sweepInt=0;
          
        }

		if(rcvn_Ok)
		{
			rcvn_Ok=false;
			internalData="_rcvn[" + String(sweepDev,DEC) + "];\n";
			fuenteCMD=4;
			Serial.println(internalData);
			ChkCMDinternal();
			delay(50);
			sweepDev++;
		}
				
	}

}

void GuardarEdo(String msg)
{
	String temp="";
	int pos0=0, pos1=0,pos2=0;
	pos0=msg.indexOf("_sndn[");
	pos1=msg.indexOf(";");

	if(pos0!=-1)
	{
		
		temp=msg.substring(pos0,pos1);
		int a=temp.substring(6).toInt();
		pos2=temp.indexOf(",")+1;
		int b=temp.substring(pos2).toInt();
		disp.Dispositivo[a].tipo=b;

	}
	
	if(RadioWriteTemp.indexOf("_rcvn[")!=-1)
	{
		disp.Dispositivo[RadioWriteTemp.substring(6).toInt()].tipo=msg.toInt();
		rcvn_Ok=true;
				
	}
	
}

void Escuchando(void){
	
	if(RF.available()){
	
		if(fuenteCMD==1){
			Serial.print("Resp del Dispositivo: ");
			ReadD=RadioRead();
			Serial.println(ReadD);
			Serial.println("ok...");
		}

		if(fuenteCMD==2){
			Serial1.print("Resp del Dispositivo: ");
			ReadD=RadioRead();
			Serial1.println(ReadD);
			Serial1.println("ok...");
		}
			
		if(fuenteCMD==3){
			wifiEnviar("Resp del Dispositivo: ");
			ReadD=RadioRead();
			wifiEnviarln(ReadD);
			wifiEnviarln("ok...");
		}
		
		if(fuenteCMD==4){
			internalResult="Resp del Dispositivo: ";
			ReadD=RadioRead();
			internalResult=internalResult + ReadD+ "\n";
			internalResult=internalResult + "ok...\n";
		}
		
		if(fuenteCMD==1)
			Serial.println(";");
		
		if(fuenteCMD==2)
			Serial1.println(";");
		
		if(fuenteCMD==3)
			wifiEnviarln(";");
		
		if(fuenteCMD==4)
			internalResult=internalResult + ";\n";
      
		delay(25);
		
		GuardarEdo(ReadD);
    ReadD="";
		
	}
	
}
