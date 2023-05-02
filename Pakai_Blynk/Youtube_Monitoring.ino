void setupYoutube()
{
  // Required if you are using ESP8266 V2.5 or above
  client.setInsecure();

  // If you want to enable some extra debugging
  api._debug = true;
}

void youtubesubs()
{
  //Youtube Subs Counter
  if (millis() > nextRunTime)  {
    if(api.getChannelStatistics(CHANNEL_ID))
    {
      lcd.clear();
      Serial.println("---------Stats---------");
      Serial.print("Subscriber Count: ");
      Serial.println(api.channelStats.subscriberCount);
      lcd.print(0, 0,(String("Subscribe: ") + String(api.channelStats.subscriberCount)));
      Blynk.virtualWrite(V6, api.channelStats.subscriberCount);
      
      Serial.print("Total Penayangan: ");
      Serial.println(api.channelStats.viewCount);
      Blynk.virtualWrite(V7, api.channelStats.viewCount);
      
      Serial.print("Total Komentar: ");
      Serial.println(api.channelStats.commentCount);
      Blynk.virtualWrite(V8, api.channelStats.commentCount);
      
      Serial.print("Total Video: ");
      Serial.println(api.channelStats.videoCount);
      lcd.print(0, 1,(String("All Video: ") + String(api.channelStats.videoCount)));
      Blynk.virtualWrite(V9, api.channelStats.videoCount);
      // Probably not needed :)
      Serial.print("hiddenSubscriberCount: ");
      Serial.println(api.channelStats.hiddenSubscriberCount);
      Serial.println("------------------------");
    }
//    delay(100);
    nextRunTime = millis() + timeBetweenRequests;
  }
}
