
uint64_t selectPipe(String _pipe)
{
  uint64_t ix= _pipe[4] + _pipe[3]*0x100 + _pipe[2]*0x10000 + _pipe[1]*0x1000000 + _pipe[0]*0x100000000;
  return(ix); 
}

String RadioRead(void)
{
  String Mensaje;
  Mensaje.reserve(16);
  Mensaje.remove(0, 15);
    
  bool a=false;
  int z=0;
  
  char MSG[16];
  
  while(!a)
	a=radio.read( MSG,15);


  for (int i = 0; i < 15; i++){
    Mensaje.concat(MSG[i]);
    if(MSG[i]==';')
      i=15;
  }

  return (Mensaje);
}

bool RadioWrite(String theMessage)
{
  bool a=false;
      char charToSend[16];
      
  theMessage.concat(';');
  
  int messageSize = theMessage.length();
  
  for (int i = 0; i < messageSize; i++) 
  {
    charToSend[i] = theMessage.charAt(i);
  }
  a=radio.write(charToSend,messageSize);  
  return (a);
}

void Duplex2Radio(int Enable)
{
	if(Enable==1)
	{
	    radio.stopListening();    // Paramos la escucha para poder hablar
		
		radio.openWritingPipe(selectPipe(disp.Dispositivo[RadioWriteTemp.substring(6).toInt()].direccion));
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
		while(!ok && TXattempts<10)
		{
			delay(75);
			ok = RadioWrite(RadioWriteTemp);
			++TXattempts;
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
				Serial.println("ok...");

			if(fuenteCMD==2)
				Serial1.println("ok...");
			
			if(fuenteCMD==3)
				wifiEnviarln("ok...");
		}
		
		else{
			if(fuenteCMD==1)
				Serial.println("Falla al transmitir");
			
			if(fuenteCMD==2)
				Serial1.println("Falla al transmitir");
			
			if(fuenteCMD==3)
				wifiEnviarln("Falla al transmitir");
		}
		
		radio.startListening();  	//Volvemos a la escucha
		radio.openReadingPipe(1,selectPipe(disp.Dispositivo[RadioWriteTemp.substring(6).toInt()].direccion)+1);
		
		unsigned long started_waiting_at = millis();
		bool timeout = false;
		while ( ! radio.available() && ! timeout )  // Esperasmos repsuesta hasta 200ms
			if (millis() - started_waiting_at > 300 )timeout = true;
		
		if ( timeout ){
				if(fuenteCMD==1)
					Serial.println("Falla en el tiempo de respuesta");
				
				if(fuenteCMD==2)
					Serial1.println("Falla en el tiempo de respuesta");
				
				if(fuenteCMD==3)
					wifiEnviarln("Falla en el tiempo de respuesta");
			}
		else
		{ // Leemos el mensaje recibido
			if(fuenteCMD==1){
				Serial.print("Resp del Dispositivo: ");
				Serial.println(RadioRead());
			}

			if(fuenteCMD==2){
				Serial1.print("Resp del Dispositivo: ");
				Serial1.println(RadioRead());
			}
			
			if(fuenteCMD==3){
				wifiEnviar("Resp del Dispositivo: ");
        wifiEnviarln(RadioRead());
        //wifiEnviarln("hola");
				fuenteCMD=0;
			}
		}
		
		if(fuenteCMD==1)
			Serial.print(";");
		
		if(fuenteCMD==2)
			Serial1.print(";");
		
		if(fuenteCMD==3)
			wifiEnviarln(";");
      
		delay(25);
		
		radio.stopListening();
		cmdOk=0;
		TXradioEn=0;		
	}
	
}




