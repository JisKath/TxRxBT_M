

void wifiSetup(void)
{
   Serial.print("WiFI setup begin\r\n");
   
   wifi.restart();
   delay(500);
   
    Serial.print("FW Version:");
    Serial.println(wifi.getVersion().c_str());
 
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
 
   if (wifi.setTCPServerTimeout(90)) {
      Serial.print("set tcp server timout 30 seconds\r\n");
   }
   else {
      Serial.print("set tcp server timout err\r\n");
   }
 
   Serial.println("WiFi setup end\r\n");

}

void btSetup (void)
{
	delay(5000);
	pinMode(13, OUTPUT);
	pinMode(BT_On, OUTPUT);										// configurar pin para alimentacion modulo BT 
	pinMode(AT_Mode, OUTPUT);									// configurar pin para habilitacion de modo AT 2

	digitalWrite(AT_Mode, LOW);
	digitalWrite(BT_On, LOW);

	Serial.println("Levantando el modulo Bluetooth");

	digitalWrite(BT_On, HIGH);
	delay(1500);
	
	digitalWrite(AT_Mode, HIGH);	
	delay(500);
	digitalWrite(AT_Mode, LOW);
	
	Serial.println("Esperando comandos AT:");	
	Serial1.begin(115200);									// Iniciar el puerto serie BT
	
}

void nrf24Setup(void)
{
	pinMode(53, OUTPUT);
	radio.begin();
	Serial.println("Levantando el modulo de radio NRF");

	radio.setDataRate(RF24_250KBPS);
	radio.setChannel(30);
	radio.setPALevel(3);
	radio.setRetries(15,15);  								// Maximos reintentos 
	radio.setPayloadSize(16);   							// Reduce el payload de 32 si tienes problemas
	radio.openWritingPipe(selectPipe(disp.Dispositivo[0].direccion));          // Abrir para escribir
	

}

void HC11Setup(void){
	HC11.cmdPin(50);										//int HC11cmdMode = 50
	HC11.ATmode(true);

	Serial.println("Configurando modulo HC11");

	Serial.println(HC11.Baudios("38400"));
	Serial.println(RF.readString());

	Serial.println(HC11.Addr("001"));
	Serial.println(RF.readString());

	Serial.println(HC11.Canal("015"));
	Serial.println(RF.readString());

	Serial.println(HC11.Potencia("8"));
	Serial.println(RF.readString());

	Serial.println(HC11.Info());
	Serial.println(RF.readString());

	Serial.println(HC11.Version());
	Serial.println(RF.readString());

	Serial.println(HC11.Function("3"));
	Serial.println(RF.readString());

	HC11.ATmode(false);
	RF.setTimeout(20);
	Serial.println("Finalizando COnfiguracion...");
	
}
