  
  
  
void wifiRecibir(void)
{
	uint8_t buffer[128] = { 0 };
	//   uint8_t mux_id;

	uint32_t len =wifi.recv(&mux_id, buffer, sizeof(buffer), 100);
	if (len > 0) {
		Serial.println("");
		Serial.println("______________________________________________");
		Serial.print("Received from: ");
		Serial.print(mux_id);
		Serial.print("\r\n");
		for (uint32_t i = 0; i < len; i++) {
			wifiData=wifiData+(char)buffer[i];
		}

		if(wifiData.length()>20){
			wifiData=(wifiData.substring(wifiData.indexOf("GET /")+5,wifiData.indexOf("HTTP")));
		}
		
		Serial.println(wifiData);

		Serial.print("Status: ");
		Serial.println("");
		Serial.println("______________________________________________");

	}
}

void wifiEnviarln(String data)
{
	data=data+"\r\n";
	wifi.sends(mux_id, data,data.length());	
}

void wifiEnviar(String data)
{
	wifi.sends(mux_id, data,data.length());	
}
