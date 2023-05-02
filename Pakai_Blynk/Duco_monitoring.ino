boolean runningTerus(unsigned long intervalnya) {
    static unsigned long previousMillisnya = 0;
    unsigned long currentMillisnya = millis();
    if (currentMillisnya - previousMillisnya >= intervalnya) {
        previousMillisnya = currentMillisnya;
        return true;
    }
    return false;
//    millis multitasking nya
}

String httpGetString(String URL) 
{
    String payload = "";
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;
    if (http.begin(client, URL)) {
        int httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK) {
            payload = http.getString();
        } else {
            Serial.printf("[HTTP] GET... losss, error: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
    }
    return payload;
}

void Duco_view()
{
  if (runningTerus(run_in_ms)) 
  {
        float totalHashrate = 0.0;
        float avgHashrate = 0.0;
        int total_miner = 0;
        int miner_accepted = 0;
        int miner_rejected = 0;
        String miner_identifier;
        String miner_software;

        String input = httpGetString(ducoReportJsonUrl);

        DynamicJsonDocument doc (5000);
        DeserializationError error = deserializeJson(doc, input);

        if (error) {
            Serial.print("deserializeJson() gagal: ");
            Serial.println(error.c_str());
            return;
        }

        JsonObject result = doc["result"];
        JsonObject result_balance = result["balance"];
        double result_balance_balance = result_balance["balance"];
        const char *result_balance_created = result_balance["created"];
        const char *result_balance_username = result_balance["username"];
        const char *result_balance_verified = result_balance["verified"];

        for (JsonObject result_miner : result["miners"].as<JsonArray>()) 
        {
            float result_miner_hashrate = result_miner["hashrate"];
            String result_miner_identifier = result_miner["identifier"];
            int result_miner_accepted = result_miner["accepted"];
            int result_miner_rejected = result_miner["rejected"];
            String result_miner_software = result_miner["software"];

            miner_identifier = result_miner_identifier;
            miner_accepted = result_miner_accepted;
            miner_rejected = result_miner_rejected;
            miner_software = result_miner_software;
     
            totalHashrate = totalHashrate + result_miner_hashrate;
            total_miner++;
        }

        avgHashrate = totalHashrate / long(total_miner);
        long run_span = run_in_ms / 1000;


/*
 * BEGIN DISPLAY
 * 
 * refreshed every 5000 ms as in 'run_in_ms' variable
 *
 * I STRONGLY RECOMMEND PUT REFRESH RATE ABOVE 5000 MS,
 * IT WILL LIGHTEN CURRENT DUINO SERVER AND YOUR BOARD MEMORY BUFFER, REALLY.
 *
 */

//        Serial.println("result_balance_username : " + String(result_balance_username));
//        Serial.println("result_balance_balance : " + String(result_balance_balance));
//        Serial.println("totalHashrate : " + String(totalHashrate));
//        Serial.println("avgHashrate H/s : " + String(avgHashrate));
//        Serial.println("total_miner : " + String(total_miner));
//        Serial.println("==================");

        Serial.println("DUCO Username  : " + String(result_balance_username));
        Serial.println("Total DUCO     : " + String(result_balance_balance));
        Serial.println("Total H/s      : " + String(totalHashrate));
        Serial.println("AVG H/s        : " + String(avgHashrate));
        Serial.println("Total Accepted : " + String(miner_accepted));
        Serial.println("Total Reject   : " + String(miner_rejected));
        Serial.println("+++++++++++++++++++++++++++++++++++++++++++");
        Serial.println("Nama RIG       : " + String(miner_identifier));
        Serial.println("Total Alat     : " + String(total_miner) + " Alat");
        Serial.println("Software       : " + String(miner_software));
        Serial.println("===================================================");

        Blynk.virtualWrite(V13, result_balance_username);
        Blynk.virtualWrite(V14, result_balance_balance);
        Blynk.virtualWrite(V15, totalHashrate);
        Blynk.virtualWrite(V16, avgHashrate);
        Blynk.virtualWrite(V17, total_miner);
        Blynk.virtualWrite(V18, miner_accepted);
        Blynk.virtualWrite(V19, miner_rejected);
        Blynk.virtualWrite(V20, miner_identifier);
        Blynk.virtualWrite(V21, miner_software);

//        terminalDuco.clear();
//        terminalDuco.println(F("Blynk V" BLYNK_VERSION " Monitor DUCO!"));
//        terminalDuco.println(F("================================"));
//        terminalDuco.println("DUCO Username  : " + String(result_balance_username));
//        terminalDuco.println("Total DUCO     : " + String(result_balance_balance));
//        terminalDuco.println("Total H/s      : " + String(totalHashrate));
//        terminalDuco.println("AVG H/s        : " + String(avgHashrate));
//        terminalDuco.println("Total Accepted : " + String(miner_accepted));
//        terminalDuco.println("Total Reject   : " + String(miner_rejected));
//        terminalDuco.println(F("+++++++++++++++++++++++++++++++++++++++++++"));
//        terminalDuco.println("Nama RIG       : " + String(miner_identifier));
//        terminalDuco.println("Total Alat     : " + String(total_miner) + " Alat");
//        terminalDuco.println("Software       : " + String(miner_software));
//        terminalDuco.flush();

    }
}
