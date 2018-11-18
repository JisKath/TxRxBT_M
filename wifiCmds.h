  
  
  
  void wifiRecibir(void)
  {
   uint8_t buffer[128] = { 0 };
   uint8_t mux_id;
 
   uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);
   if (len > 0) {
    Serial.println("");
    Serial.println("______________________________________________");
      Serial.print("Received from: ");
      Serial.print(mux_id);
      Serial.print("\r\n");
      for (uint32_t i = 0; i < len; i++) {
		wifiData=wifiData+(char)buffer[i];
         //Serial.print((char)buffer[i]);
      }
	  
      if (wifi.releaseTCP(mux_id)) {
         /*Serial.print("release tcp ");
         Serial.print(mux_id);
         Serial.println(" ok");*/
		 Serial.println(wifiData.substring(wifiData.indexOf("GET /")+5,wifiData.indexOf("HTTP")));
      }
      else {
         Serial.print("release tcp");
         Serial.print(mux_id);
         Serial.println(" err");
      }
 
      Serial.print("Status: ");
      Serial.print(wifi.getIPStatus().c_str());
      Serial.println("");
      Serial.println("______________________________________________");
      
	  
	  wifiData="";
   }
  }