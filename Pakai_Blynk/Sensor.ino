void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int sensorLDR = analogRead(ldrPin);
  

  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal membaca sensor!");
    Blynk.virtualWrite(V0, "DHT Sensor Tidak Terbaca!");
//    digitalWrite(ledPin, HIGH);
    return;
  }
//  digitalWrite(ledPin, LOW);
  Blynk.virtualWrite(V0, "DHT Sensor Terbaca!");
  Blynk.virtualWrite(V2, t); //suhu celciusnya //
  Blynk.virtualWrite(V3, h); //humiditynya //
  Blynk.virtualWrite(V22, (t*9)/5+32); //Fahrenheit  (celcius * 9)/ 5 + 32 //
  Blynk.virtualWrite(V23, t+273.15); //Kelvin   celsius + 273.15 //
  Blynk.virtualWrite(V24, (t*4)/5); //Reamur  (celcius*4)/5 //
  
//  Blynk.virtualWrite(V0, sensorLDR);
}

void setupSensor()
{
  //Sensor Suhu dan LDR
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}
