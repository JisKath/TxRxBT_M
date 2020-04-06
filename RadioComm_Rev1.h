
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
	
		if (ok){
			if(fuenteCMD==1)
				Serial.println("Envio satisfactorio");

			if(fuenteCMD==2)
				Serial1.println("Envio satisfactorio");
			
			if(fuenteCMD==3)
				wifiEnviarln("Envio satisfactorio");
		}
		
		else{
			if(fuenteCMD==1)
				Serial.println("Falla al transmitir");
			
			if(fuenteCMD==2)
				Serial1.println("Falla al transmitir");
			
			if(fuenteCMD==3)
				wifiEnviarln("Falla al transmitir");
		}
		
		cmdOk=0;
		TXradioEn=0;
		
	}
	
}

void Escuchando(void){
	
	if(RF.available()){
	
		if(fuenteCMD==1){
			Serial.print("Resp del Dispositivo: ");
			Serial.println(RadioRead());
			Serial.println("ok...");
		}

		if(fuenteCMD==2){
			Serial1.print("Resp del Dispositivo: ");
			Serial1.println(RadioRead());
			Serial1.println("ok...");
		}
			
		if(fuenteCMD==3){
			wifiEnviar("Resp del Dispositivo: ");
			wifiEnviarln(RadioRead());
			wifiEnviarln("ok...");
		}
		
		if(fuenteCMD==1)
			Serial.println(";");
		
		if(fuenteCMD==2)
			Serial1.println(";");
		
		if(fuenteCMD==3)
			wifiEnviarln(";");
      
		delay(25);
		
	}
	
}
