#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "esp8266dansensor-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "jME3lDZg2t7p07wPLF2Qe1RUIjXahEpRGFLRZExf"
#define WIFI_SSID "Silviaaaa"
#define WIFI_PASSWORD "123456789"

int Gas_analog = A0;

void setup() {
  pinMode(Gas_analog, INPUT);
  Serial.begin(115200);
  delay(500);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  int gas = analogRead(Gas_analog);

  Serial.print("Gas Sensor : ");
  Serial.print(gas);
  Serial.print("\t");
    if (gas > 700) {
      Serial.println("Gas");
      delay(100);
    }else{
      Serial.println("Tidak Ada Gas");
    }
    delay(100);

   Firebase.pushInt("Gas", gas);
   if (Firebase.failed()){
   Serial.println("logs failed: ");
   Serial.println(Firebase.error());
   return;
   }
}
