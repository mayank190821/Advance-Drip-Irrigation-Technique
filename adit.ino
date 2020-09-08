/*
   Author: Mayank Bhugra
   Project Name: Advance Drip Irrigation Technique(ADIT)
   Date: 14/Feb/2020
*/
#include<ESP8266WiFi.h>
#include<FirebaseArduino.h>
#define host "adit-ms819.firebaseio.com"
#define auth "09eORK2VN9f4eiWemXZlo4QMHu5G1ThX4WLXE1tF"
#define wifiname "mayank"
#define wifipass "12345678"

int output_value, wheat, onion, carrot, potato, h = 0;
int degree;

void setup() {
  Serial.begin(9600);
  WiFi.begin(wifiname, wifipass);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Reading From the Sensor ...");
  pinMode(A0, INPUT);
  Firebase.begin(host, auth);
  Firebase.setInt("W", 0);
  Firebase.setInt("C", 0);
  Firebase.setInt("O", 0);
  Firebase.setInt("P", 0);
  Firebase.setInt("H", 0);
  pinMode(D0, OUTPUT);
  delay(2000);
}
void fic() {
  Serial.print("try to connect");
  Firebase.begin(host, auth);
}
void loop() {
  if (Firebase.failed())
  {
    Serial.print("setting no. failed:");
    Serial.print(Firebase.error());
    fic();
    return;
  }
  wheat = Firebase.getString("W").toInt(); //40
  onion = Firebase.getString("O").toInt(); //78%
  carrot = Firebase.getString("C").toInt(); //50%
  potato = Firebase.getString("P").toInt(); //72%
  output_value = analogRead(A0);
  output_value = map(output_value, 1023, 0, 0, 100);
  Serial.print(output_value);
  Firebase.setInt("H", output_value);
  if (onion == 1)
  {
    if (output_value < 78)
    {
      digitalWrite(D0, 0);
    }
    else
    {
      //off condition
      onion = 0;
      digitalWrite(D0, 1);
    }
  }
  if (wheat == 1)
  {
    if (output_value < 24)
    {
      digitalWrite(D0, 0);
    }
    else
    {
      //off condition
      wheat = 0;
      digitalWrite(D0, 1);
    }
  }
  if (carrot == 1)
  {
    if (output_value < 50)
    {
      digitalWrite(D0, 0);
    }
    else
    {
      //off condition
      carrot = 0;
      digitalWrite(D0, 1);
    }
  }
  if (potato == 1)
  {
    if (output_value <= 72)
    {
      digitalWrite(D0, 0);
    }
    else
    {
      //off condition
      potato = 0;
      digitalWrite(D0, 1);
    }
  }
  delay(2000);
}
