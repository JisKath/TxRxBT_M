
void htmlPagina(void)
{
  #define wifiWrite(A) wifi.send(mux_id, (uint8_t*) A, sizeof(A) - 1);
    #define wifiWritee(A) wifi.send(mux_id, (uint8_t*) A, 1);
  String Test="AB";

  //Serial2.println("AT");
  //wifiWrite("Que pedro pablo");
  wifiWrite("HTTP/1.1 200 OK\r\n");
  wifiWrite("Content-Type: text/html\r\n");
  wifiWrite("Connection: close\r\n");  // the connection will be closed after completion of the response
  wifiWrite("<!DOCTYPE html>\r\n");
  wifiWrite("\r\n");
  wifiWrite("<html>\r\n");

  wifiWrite("<html><head><title>Domo Haus</title></head><body>\r\n");
  wifiWrite("<h1><em><strong><span style=\"color: #00ff00;\">Comando"); 
  //wifiWritee((uint8_t)&Test);
   wifiWrite("Recibidoo</span></strong></em></h1>\r\n"); 
  wifiWrite("<h2 style=\"color: #2e6c80;\"><span style=\"color: #008080;\"><strong><enm>_XXXXXXXXX</em></strong></span></h2>\r\n"); 
  wifiWrite("<p><span style=\"color: #008080;\"><strong><em>Fin</em></strong></span></p>\r\n"); 
  wifiWrite("</body></html>\r\n");
  wifiWrite("</html>\r\n"); 
}
