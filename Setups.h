void inicializarDev(void)
{
	Serial.begin(115200);   						// Iniciar  el puerto serie
	pinMode(13, OUTPUT);
	
	Serial.println("enviando EEPROM a SRAM");		//Inicializando memoria
	disp.reeprom();
  escenario.rSeeprom();
	Serial.println("EEPROM ---> SRAM");
}

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
	Serial.println("Finalizando Configuracion de HC-11...\n");
	
}

void inicializarTimers(void)
{
	blinkOn.TON.pre=100;							//Inicilizando Timers
	blinkOff.TON.pre=100;
	wifiSta.TON.pre=60000;
	blinkOn.TON.en=0;
	blinkOff.TON.en=0;
	wifiSta.TON.en=0;
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

void	rtcSetup(void)										//Inicializando Modulo RTC
{
	// prepare the RTC class, this also calls Wire.begin()
	GFRTC.begin(true);
	
	  // check if we can communicate with RTC
	if (GFRTC.isPresent()) {
		Serial.println("RTC connected and ready.");
	} else {
		Serial.println("Check RTC connections and try again.");
	for (;;);
	}
	
	// get date and time
	if (GFRTC.read(datetime)) {
		// read ok, print data from RTC
		Serial.print(F("OK, Time = "));
		print2digits(datetime.tm_hour);
		Serial.write(':');
		print2digits(datetime.tm_min);
		Serial.write(':');
		print2digits(datetime.tm_sec);
		Serial.print(F(", Date (D/M/Y) = "));
		Serial.print(datetime.tm_mday);
		Serial.write('/');
		Serial.print(datetime.tm_mon);
		Serial.write('/');
		Serial.print(timelib_tm2y2k(datetime.tm_year));
		Serial.println();
		
		if(timelib_tm2y2k(datetime.tm_year)<18)
		{
			skipSetFecha=false;
		}
		
	} else {
		// error reading the RTC
		Serial.println(F("Cannot read RTC."));
	}
	
	if(!skipSetFecha){
		// use the datetime structure to group date time information
		// SET THE DESIRED TIME / DATE HERE
		datetime.tm_hour = 12;
		datetime.tm_min = 0;
		datetime.tm_sec = 0;
		datetime.tm_wday = 3;
		datetime.tm_mday = 14;
		datetime.tm_mon = 4;
		datetime.tm_year =timelib_y2k2tm(20);
		
		// write data on struct to RTC registers
		if (GFRTC.write(datetime)) {
			// write ok, print data sent to RTC
			Serial.print(F("Set date / time to: "));
			print2digits(datetime.tm_hour);
			Serial.write(':');
			print2digits(datetime.tm_min);
			Serial.write(':');
			print2digits(datetime.tm_sec);
			Serial.print(F(", Date (D/M/Y) = "));
			Serial.print(datetime.tm_mday);
			Serial.write('/');
			Serial.print(datetime.tm_mon);
			Serial.write('/');
			Serial.print(timelib_tm2y2k(datetime.tm_year));
			Serial.println();
		} else {
			// error reading the RTC
			Serial.println(F("Cannot write RTC."));
		}
	}	
}
