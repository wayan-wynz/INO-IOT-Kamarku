boolean runningInfoDevice(unsigned long intervaldevice) {
    static unsigned long previousMillisDevice = 0;
    unsigned long currentMillisDevice = millis();
    if (currentMillisDevice - previousMillisDevice >= intervaldevice) {
        previousMillisDevice = currentMillisDevice;
        return true;
    }
    return false;
}

void InfoDevice()
{
  float hum = dht.readHumidity();
  float tem = dht.readTemperature();
  if (runningInfoDevice(60000))
  {
    Blynk.virtualWrite(V28, WiFi.localIP().toString());
    
    terminal_device.clear(); //Memulai terminal
    
    terminal_device.println(F("Blynk V" BLYNK_VERSION ": IOT Kamarku!"));
    terminal_device.println(F("By I WAYAN SUJANE"));
    terminal_device.println(F("==============================================="));
    terminal_device.println(F("INFORMASI PERANGKAT NodeMCU"));
    terminal_device.println(F("==============================================="));
    terminal_device.print(F("IP Address     : "));
    terminal_device.println(WiFi.localIP());
    terminal_device.print(F("SSID           : "));
    terminal_device.println(ssid);
    terminal_device.print(F("MAC            : "));
    terminal_device.println(WiFi.macAddress());

    WiFiClient wClient;
    const int httpPort = 80;
    if(!wClient.connect(serverhosting, httpPort))
    {
//      Serial.println("Gagal koneksi ke Server");
      Blynk.virtualWrite(V25, "Gagal Koneksi ke Server!");

      terminal_device.println(F("==============================================="));
      terminal_device.println(F("KONEKSI KE HOSTING SERVER"));
      terminal_device.println(F("==============================================="));
      terminal_device.print(F("Alamat Server  : "));
      terminal_device.println(serverhosting);
      terminal_device.println(F("Koneksi Server : Terputus"));
      terminal_device.print(F("Status Data    : - "));
      terminal_device.flush(); //Menutup Terminal
      return;
    }
    //proses pengiriman data ketika terkoneksi ke server
    Blynk.virtualWrite(V25, "Berhasil Koneksi ke Server!");
    String url;
    HTTPClient http;
    //link pengiriman pada website native
//    url = "http://" + String(serverhosting) + "/sensor-iot/kirimdata.php?suhu=" + String(tem) + "&kelembaban=" + String(hum);
    
    //apabila sudah dihosting maka gunakan yang di bawah
    url = "http://" + String(serverhosting) + "/config/kirimdata.php?suhu=" + String(tem) + "&kelembaban=" + String(hum);
    
    //eksekusi url
    http.begin(wClient, url);
    http.GET();
    String respon = http.getString();

    respon.trim();
    if(respon != "")
    {
      //format data, misal "10#29#89" = array (setelah parsing)
      //parsing data (pecah data)
      int index = 0;
      for(int i=0; i<=respon.length(); i++)
      {
        char delimiter = '#';
        if(respon[i] != delimiter)
          arrData[index] += respon[i];
        else
          index++; //variabel index bertambah 1
      }

      terminal_device.println(F("==============================================="));
      terminal_device.println(F("KONEKSI KE HOSTING SERVER"));
      terminal_device.println(F("==============================================="));
      terminal_device.print(F("Alamat Server  : "));
      terminal_device.println(serverhosting);
      terminal_device.println(F("Koneksi Server : Terhubung"));
      terminal_device.println(F("-----------------------------------------------"));
      terminal_device.println(F("PENGIRIMAN KE DATABASE SERVER"));
      terminal_device.println(F("-----------------------------------------------"));
      terminal_device.print(F("Status Data    : "));
      terminal_device.println(arrData[0]);
      terminal_device.print(F("Jumlah Data DB : "));
      terminal_device.print(arrData[1]);
      terminal_device.println(" Data(Rows)");
//      terminal_device.println(respon);
  
      terminal_device.flush(); //Menutup Terminal
      http.end();

      Blynk.virtualWrite(V26, arrData[1]);

      arrData[0] = "";
      arrData[1] = "";
//      arrData[2] = "";
      
    }

//    terminal_device.println(F("------------------------------------"));
//    terminal_device.println(F("Koneksi Data ke Hosting Server"));
//    terminal_device.print(F("Alamat Server  : "));
//    terminal_device.println(serverhosting);
//    terminal_device.println(F("Koneksi Server : Terhubung"));
//    terminal_device.print(F("Status Data    : "));
//    terminal_device.println(respon);
//
//    terminal_device.flush(); //Menutup Terminal
//    http.end();

  }
}
