
uint64_t selectPipe(String _pipe)
{
  uint64_t ix= _pipe[4] + _pipe[3]*0x100 + _pipe[2]*0x10000 + _pipe[1]*0x1000000 + _pipe[0]*0x100000000;
  return(ix); 
}

String RadioRead(void)
{
  String Mensaje="";
  bool a=false;
  int z=0;
  
  char MSG[16];
  
  while(!a)
	a=radio.read( MSG,15);


  for (int i = 0; i < 15; i++) 
    Mensaje.concat(MSG[i]);

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
		
		Serial1.print("Enviando  ");
		Serial1.println(RadioWriteTemp);
		
		bool ok = false;
		int TXattempts=0;
		while(!ok && TXattempts<10)
		{
			delay(75);
			ok = RadioWrite(RadioWriteTemp);
			++TXattempts;
		}
		
    Serial1.print("Intentos: ");
    Serial1.println(TXattempts);
	
		if (ok)
			Serial1.println("ok...");
		else
			Serial1.println("Falla al transmitir");

		radio.startListening();  	//Volvemos a la escucha
		radio.openReadingPipe(1,selectPipe(disp.Dispositivo[RadioWriteTemp.substring(6).toInt()].direccion)+1);
		
		unsigned long started_waiting_at = millis();
		bool timeout = false;
		while ( ! radio.available() && ! timeout )  // Esperasmos repsuesta hasta 200ms
			if (millis() - started_waiting_at > 300 )timeout = true;
		
		if ( timeout )
			 Serial1.println("Falla en el tiempo de respuesta");
		else
		  { // Leemos el mensaje recibido

			Serial1.print("Resp del Dispositivo: ");
			Serial1.println(RadioRead());
			//Serial1.print(";");
		  }
		Serial1.print(";");
		delay(25);
		
		radio.stopListening();
		cmdOk=0;
		TXradioEn=0;		
	}
	
}

