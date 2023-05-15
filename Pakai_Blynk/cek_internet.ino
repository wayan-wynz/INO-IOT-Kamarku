boolean millisTesInternet(unsigned long intervalTesPing) {
    static unsigned long previousMillisTesPing = 0;
    unsigned long currentMillisTesPing = millis();
    if (currentMillisTesPing - previousMillisTesPing >= intervalTesPing) {
        previousMillisTesPing = currentMillisTesPing;
        return true;
    }
    return false;
}

void cekInternet()
{
  if (millisTesInternet(3000))
  {
//    Serial.print("Pinging host ");
//    Serial.println(remote_host);
      Serial.print("RSSI : ");
      Serial.println(WiFi.RSSI());
//      Sinyal =  WiFi.RSSI().toString();
//      Blynk.virtualWrite(V27, Sinyal);
      Blynk.virtualWrite(V27, String(WiFi.RSSI()));
  
    if(Ping.ping(remote_host)) {
      Serial.println("Internet Terhubung!!");
//      Serial.print("RSSI : ");
//      Serial.println(WiFi.RSSI());
  //    digitalWrite(LED_PIN, HIGH);
      digitalWrite(ledPin, LOW);
    } else {
      Serial.println("Terputus !!");
//      Serial.print("RSSI : ");
//      Serial.println(WiFi.RSSI());
  //    digitalWrite(LED_PIN, LOW);
      digitalWrite(ledPin, HIGH);
    }  
  }
}
