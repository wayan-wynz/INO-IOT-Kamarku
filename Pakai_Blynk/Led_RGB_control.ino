BLYNK_WRITE(V1)
{
  r = param[0].asInt();
  g = param[1].asInt();
  b = param[2].asInt();
  static1(r, g, b,data);
}

BLYNK_WRITE(V4)
{
data = param.asInt(); 
static1(r, g, b,data);
}
void static1(int r, int g, int b,int brightness)
{
  FastLED.setBrightness(brightness);
  for (int i = 0; i < NUM_LEDS1; i++ )
  {
    leds1[i] = CRGB(r, g, b);
  }
  FastLED.show();
}
