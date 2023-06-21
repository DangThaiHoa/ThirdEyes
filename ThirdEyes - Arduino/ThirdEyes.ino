#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
FirebaseData dulieu;

const int TRIG_PIN = 5;
int ECHO_PIN = 4;

void ketnoiwifi()
{
  Serial.println("Bat dau ket noi.");
  WiFi.begin("CITIGYM-STAFF","Citigym@123");
  while(!(WiFi.status()==WL_CONNECTED)) {
    delay(500);
    Serial.println("...");
  }
  Serial.println("Ket noi thanh cong!");
}

void setup() {
  Serial.begin(115200);
  ketnoiwifi(); 
  Firebase.begin("thirdeyeapp-4891f-default-rtdb.firebaseio.com","YyXAyIvjp7vndC7GNuUY8IgmC7bY3KZIM1DDJl9O");
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  long duration, distanceCm;
   
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN,HIGH);

  distanceCm = duration / 29.1 / 2;

  if (distanceCm < 0) {
    Firebase.setFloat(dulieu,"Distance",0);
    Serial.println("Too close");
  } else if (distanceCm > 200) {
    Firebase.setFloat(dulieu,"Distance",200);
    Serial.println("Too far");
  } else {
    Firebase.setFloat(dulieu,"Distance",distanceCm);
    Serial.print(distanceCm);
    Serial.print("cm");
    Serial.println();
  }
  delay(1000);
}
