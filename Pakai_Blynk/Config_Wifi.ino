void setupWifi()
{
  //koneksi ke WiFi
//  if(!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
//  {
//    Serial.println("STA Gagal Tersetting");
//  }
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  //cek koneksi
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(ledPin, HIGH);
    digitalWrite(relay, LOW);
  }
  //apabila terkoneksi
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(ledPin, LOW);
  digitalWrite(relay, HIGH);
//  lcd1.clear();
//  lcd1.print(4, 0, "IP ADDRESS");
//  lcd1.print(3, 1, WiFi.localIP());
}
