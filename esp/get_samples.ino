#include <driver/adc.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "FFT.h"

const int ADC_PIN = 32;
const float VREF = 3.3;  // set the ADC reference voltage


const char* ssid = "esp";
const char* password = "wififoresp";
const char* serverUrl = "http://192.168.0.198:3000/data";

const int numReadings = 16;
float sensorValues[numReadings];
float fft_input[numReadings];
float fft_output[numReadings];
int readingsIndex = 0;
float max_magnitude = 0;
float fundamental_freq = 0;
float delaySeconds = 100 / 1000000;

void readSensor(float sensorValues[], int& readingsIndex) {
  int sensorValue = analogRead(ADC_PIN);  // Replace A0 with the appropriate pin for your sensor
  Serial.println(sensorValue);
  sensorValues[readingsIndex] = sensorValue;
  // readingsIndex = (readingsIndex + 1) % numReadings;
  readingsIndex = readingsIndex + 1;
}

void sendData(float sensorValues[], float fft_output[], float max_magnitude) {
  HTTPClient http;
  http.begin(serverUrl);

  // Set the content type header
  http.addHeader("Content-Type", "application/json");

  // Create a JSON payload with the array data
  DynamicJsonDocument doc(1024);  // Create a JSON document

  // Create an empty array for "data"
  JsonArray dataArr = doc.createNestedArray("data");
  for (int i = 0; i < numReadings; i++) {
    dataArr.add(sensorValues[i]);
  }

  // Create an empty array for "fft_data"
  JsonArray fftDataArr = doc.createNestedArray("fft_data");
  for (int i = 0; i < numReadings; i++) {
    fftDataArr.add(fft_output[i]);
  }

  JsonArray maxMagArr = doc.createNestedArray("maxMag");
  maxMagArr.add(max_magnitude);

  // Serialize the JSON document to a string
  String payload;
  serializeJson(doc, payload);

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

  fft_config_t* real_fft_plan = fft_init(numReadings, FFT_REAL, FFT_FORWARD, fft_input, fft_output);
  for (int k = 0; k < numReadings; k++)
    real_fft_plan->input[k] = (float)sensorValues[k];

  char print_buf[300];

  long int t1 = micros();
  // Execute transformation
  fft_execute(real_fft_plan);

  // Print the output
  for (int k = 1; k < real_fft_plan->size / 2; k++) {
    /*The real part of a magnitude at a frequency is followed by the corresponding imaginary part in the output*/
    float mag = sqrt(pow(real_fft_plan->output[2 * k], 2) + pow(real_fft_plan->output[2 * k + 1], 2)) / 1;
    float freq = k * 1.0 / 0.0001;
    //    sprintf(print_buf,"%f Hz : %f", freq, mag);
    //    Serial.println(print_buf);
    if (mag > max_magnitude) {
      max_magnitude = mag;
      fundamental_freq = freq;
    }
  }
  long int t2 = micros();

  // Clean up at the end to free the memory allocated
  fft_destroy(real_fft_plan);

  sendData(sensorValues, fft_output, max_magnitude);
  // resetArray();
  readingsIndex = 0;

  // wait for a short period of time before taking the next sample
  delayMicroseconds(100);
}