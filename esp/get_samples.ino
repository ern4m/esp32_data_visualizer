#include <driver/adc.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "FFT.h"

const int ADC_PIN = 36;
const float VREF = 3.3; // set the ADC reference voltage


const char* ssid = "WIFI_ID";
const char* password = "WIFI_PASS";
const char* serverUrl = "http://$your_ip$:3000/data";

const int numReadings = 16;
int sensorValues[numReadings];
int readingsIndex = 0;

void readSensor(int sensorValues[], int& readingsIndex) {
  int sensorValue = analogRead(ADC_PIN); // Replace A0 with the appropriate pin for your sensor
  sensorValues[readingsIndex] = sensorValue;
  // readingsIndex = (readingsIndex + 1) % numReadings;
  readingsIndex = readingsIndex + 1;
}

void sendData(int sensorValues[]) {
  Serial.println("Array data:");
  for (int i = 0; i < numReadings; i++) {
    Serial.print(sensorValues[i]);
    Serial.print(" ");
  }
  Serial.println();

  HTTPClient http;
  http.begin(serverUrl);

  // Set the content type header
  http.addHeader("Content-Type", "application/json");

  // Create a JSON payload with the array data
  String payload = "[";
  for (int i = 0; i < numReadings; i++) {
    payload += String(sensorValues[i]);
    if (i != numReadings - 1) {
      payload += ",";
    }
  }
  payload += "]";

  // Send the POST request with the payload
  int httpResponseCode = http.POST(payload);
  if (httpResponseCode > 0) {
    Serial.printf("HTTP POST success. Response code: %d\n", httpResponseCode);
  } else {
    Serial.printf("HTTP POST failed. Error code: %s\n", http.errorToString(httpResponseCode).c_str());
  }

  http.end();
}

void resetArray() {
  for (int i = 0; i < numReadings; i++) {
    sensorValues[i] = 0;
  }
}

void setup() {
  // initialize ADC
  adc1_config_width(ADC_WIDTH_BIT_12);

  // initialize serial communication
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

}

void loop() {

  while (readingsIndex < numReadings) {
    readSensor(sensorValues, readingsIndex);
  }

  Serial.println("Array data:");
  for (int i = 0; i < numReadings; i++) {
    Serial.print(sensorValues[i]);
    Serial.print(" ");
  }
  Serial.println();
  sendData(sensorValues);
  readingsIndex = 0;
  
  // readSensor();
  // sendData();
  // resetArray();

  // loop f
  // read ADC value
  // uint16_t raw_value = adc1_get_raw(ADC_PIN);

  // // convert raw value to voltage
  // float voltage = raw_value / 4095.0 * VREF;
  // // print voltage to serial monitor
  // // Serial.print("ADC voltage: ");
  // Serial.println(raw_value);

  // wait for a short period of time before taking the next sample
  delayMicroseconds(5);
}