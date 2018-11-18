

void wifiSetup(void)
{
   Serial.begin(115200);
   Serial.print("setup begin\r\n");
   
   wifi.restart();
   delay(500);
 
   if (wifi.setOprToStationSoftAP()) {
      Serial.print("to station + softap ok\r\n");
   }
   else {
      Serial.print("to station + softap err\r\n");
   }
 
   if (wifi.joinAP(SSID, PASSWORD)) {
      Serial.print("Join AP success\r\n");
      Serial.print("IP: ");
      Serial.println(wifi.getLocalIP().c_str());
   }
   else {
      Serial.print("Join AP failure\r\n");
   }
 
   if (wifi.enableMUX()) {
      Serial.print("multiple ok\r\n");
   }
   else {
      Serial.print("multiple err\r\n");
   }
 
   if (wifi.startTCPServer(80)) {
      Serial.print("start tcp server ok\r\n");
   }
   else {
      Serial.print("start tcp server err\r\n");
   }
 
   if (wifi.setTCPServerTimeout(10)) {
      Serial.print("set tcp server timout 10 seconds\r\n");
   }
   else {
      Serial.print("set tcp server timout err\r\n");
   }
 
   Serial.println("setup end\r\n");

}

void btSetup (void)
{
	delay(5000);
	pinMode(13, OUTPUT);
	pinMode(BT_On, OUTPUT);			// configurar pin para alimentacion modulo BT 
	pinMode(AT_Mode, OUTPUT);		// configurar pin para habilitacion de modo AT 2

	digitalWrite(AT_Mode, LOW);
	digitalWrite(BT_On, LOW);

	Serial.println("Levantando el modulo Bluetooth");

	digitalWrite(BT_On, HIGH);
	delay(1500);
	
	digitalWrite(AT_Mode, HIGH);	
	delay(500);
	digitalWrite(AT_Mode, LOW);
	
	Serial.println("Esperando comandos AT:");	
	Serial1.begin(115200);				// Iniciar el puerto serie BT
	
}

void nrf24Setup(void)
{
	pinMode(53, OUTPUT);
	radio.begin();
	Serial.println("Levantando el modulo de radio NRF");

	radio.setDataRate(RF24_250KBPS);
	radio.setChannel(30);
	radio.setPALevel(3);
	radio.setRetries(15,15);  	// Maximos reintentos 
	radio.setPayloadSize(16);   // Reduce el payload de 32 si tienes problemas
	radio.openWritingPipe(selectPipe(disp.Dispositivo[0].direccion));          // Abrir para escribir
	

}