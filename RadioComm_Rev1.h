
String selectPipe(String _pipe)
{
  //uint64_t ix= _pipe[4] + _pipe[3]*0x100 + _pipe[2]*0x10000 + _pipe[1]*0x1000000 + _pipe[0]*0x100000000;
  String ix="0";
  ix=ix + _pipe.substring(0,2);
  return(ix); 
}

String selectPipeL(String _pipe)
{

  //uint64_t ix= _pipe[0] + _pipe[1]*0x100 + _pipe[2]*0x10000 + _pipe[3]*0x1000000 + _pipe[4]*0x100000000;
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
  //Mensaje.remove(Mensaje.indexOf(';'),Mensaje.length()-Mensaje.indexOf(';'));

  return (Mensaje);
}

bool RadioWrite(String theMessage)
{
  bool a=false;
      
  //theMessage.concat(';');
  HC11.sends(theMessage);
  
  a=true;
  
  return (a);
}

void Duplex2Radio(int Enable)
{
	if(Enable==1)
	{
	    //radio.stopListening();    // Paramos la escucha para poder hablar
		
		//radio.openWritingPipe(selectPipe(disp.Dispositivo[RadioWriteTemp.substring(6).toInt()].direccion));

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
			ok = RadioWrite(RadioWriteTemp);			//Agregar condición if cuando Ok es true, para no duplicar acción
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
		
		//radio.startListening();  	//Volvemos a la escucha
		//radio.openReadingPipe(1,selectPipeL(disp.Dispositivo[RadioWriteTemp.substring(6).toInt()].direccion)); //Cambiar el canal de la escucha por otro i.e. "CANAL" --> "LANAC"
	
		
		//radio.stopListening();
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
			//wifiEnviarln("hola");
			//fuenteCMD=0;
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
