
uint64_t selectPipe(String _pipe)
{
  uint64_t ix= _pipe[4] + _pipe[3]*0x100 + _pipe[2]*0x10000 + _pipe[1]*0x1000000 + _pipe[0]*0x100000000;
  return(ix); 
}
 
bool RadioWrite(String theMessage)

{
  
  bool a=false;
  theMessage.concat(';');
  
  int messageSize = theMessage.length();
  
  for (int i = 0; i < messageSize; i++) 
  {
    char charToSend[1];
    charToSend[0] = theMessage.charAt(i);
    radio.write(charToSend,messageSize);  
  }
  return (a);
}

void TXDatos2Radio(int Enable)
{
bool ok = false;
String theMessage="";
int msg[1];

	if(Enable==1)
		{
		
		radio.openWritingPipe(selectPipe(disp.Dispositivo[RadioWriteTemp.substring(6).toInt()].direccion));
		delay(10);
		
		ok = RadioWrite(RadioWriteTemp.substring(RadioWriteTemp.indexOf(',')+1,RadioWriteTemp.lastIndexOf(']')));
		ok=true;
    delay(10);
		if (ok)
		{
			radio.powerDown ();
			radio.powerUp();
			delay(5);
			
			//radio.openReadingPipe(1,(selectPipe(disp.Dispositivo[RadioWriteTemp.substring(6).toInt()].direccion))+1);
			radio.openReadingPipe(1,0x63616E616DLL);
			radio.startListening();
			delay(10);
			
			for(int j=0; j<1000;j++)
			{
				if (radio.available())
				{
					bool done = false;  
					done = radio.read(msg, 1); 
					char theChar = msg[0];
				  
					if (msg[0] != ';')
					{
						theMessage.concat(theChar);
					}
					else 
					{
						Serial1.println(theMessage);
						Serial1.println("_sndn Ok");
					}
				}			
			}
			
			radio.stopListening();
			delay(5);
			radio.powerDown ();
			delay(5);
			radio.powerUp();
			delay(5);
		}
		else
			Serial1.println("_sndn Fallido");
		
		RadioWriteTemp="";
		theMessage= "";
		
		ok=false;
		cmdOk=0;
		TXradioEn=0;
		}
	
}


