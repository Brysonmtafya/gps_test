#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

// Define GPS module serial connection
#define RXD2 16
#define TXD2 17
HardwareSerial gpsSerial(2); // Use Serial2 on ESP32
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200); // Start Serial Monitor
  gpsSerial.begin(9600, SERIAL_8N1, RXD2, TXD2); // Start GPS serial
  Serial.println("GPS Module Test");
}

void loop() {
  // Read data from GPS module
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      displayGPSInfo();
    }
  }

  // If no data received for 5 seconds, print error
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println("No GPS data received: check wiring");
    while (true);
  }
}

void displayGPSInfo() {
  // Display latitude and longitude
  if (gps.location.isValid()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
  } else {
    Serial.println("Location: Not Available");
  }

  // Display date and time
  if (gps.date.isValid()) {
    Serial.print("Date: ");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.println(gps.date.year());
  }

  if (gps.time.isValid()) {
    Serial.print("Time: ");
    Serial.print(gps.time.hour());
    Serial.print(":");
    Serial.print(gps.time.minute());
    Serial.print(":");
    Serial.println(gps.time.second());
  }

  delay(1000);
}