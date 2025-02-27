#define BLYNK_TEMPLATE_ID "###"   //enter id
#define BLYNK_TEMPLATE_NAME "Crop Monitoring"
#define BLYNK_AUTH_TOKEN "###"  // enter token

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHT_PIN D1               // DHT11 connected to D1
#define DHT_TYPE DHT11           // Define DHT11 sensor
#define SOIL_MOISTURE_PIN A0     // Soil moisture sensor connected to A0
#define RELAY_PIN D2             // Relay for irrigation connected to D2

// Wi-Fi credentials
char ssid[] = "###";
char pass[] = "###";

// Initialize DHT sensor
DHT dht(DHT_PIN, DHT_TYPE);

// Variables for sensor readings
float humidity, temperature;
int soilMoistureValue;

// Blynk virtual pins (Direct assignment)
#define V1 1  // Humidity
#define V2 2  // Temperature
#define V3 3  // Soil moisture level

void setup() {
  // Setup pins
  pinMode(DHT_PIN, INPUT);
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  // Initialize components
  digitalWrite(RELAY_PIN, LOW); // Start with relay OFF

  // Start Serial Monitor
  Serial.begin(115200);
  Serial.println("ESP8266 Smart Irrigation System");

  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();
}

  // Send welcome notification when the system starts
//   Blynk.logEvent("agriculture_monitoring_system_started", "Welcome to the Smart Agriculture Monitoring System!");
// }

void loop() {
  // Read DHT11 sensor
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // Check if the DHT11 sensor returned NaN (invalid reading)
  if (isnan(humidity) || isnan(temperature)) {
    Blynk.logEvent("sensor_failure", "DHT11 Sensor failure!"); // Notify user
    delay(1000);  // Delay to avoid multiple alerts in a short time
  }
  // Read soil moisture
  soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);

  // // Check for circuit disconnection (if sensor value is invalid, like 0)
  // if (soilMoisturePercent == 0) {
  //   Blynk.logEvent("circuit_break", "Circuit Disconnected!"); // Notify user
  //   delay(1000);
  // }

  // Send readings to Blynk
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, temperature);
  Blynk.virtualWrite(V3, map(soilMoistureValue, 0, 1023, 0, 100)); // Map soil moisture to 0-100

  // Display readings in Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%, Temperature: ");
  Serial.print(temperature);
  Serial.print("°C, Soil Moisture: ");
  Serial.print(map(soilMoistureValue, 0, 1023, 0, 100));
  Serial.println("%");

  // Automatic irrigation control
  int soilMoisturePercent = map(soilMoistureValue, 0, 1023, 0, 100); // Map soil moisture to 0-100%
  if (soilMoisturePercent < 20) {
    digitalWrite(RELAY_PIN, HIGH); // Turn ON relay
     Blynk.logEvent("low_water", "Water level above 90%. Irrigation ON!");
  } else if (soilMoisturePercent > 90) {
    digitalWrite(RELAY_PIN, LOW); // Turn OFF relay
    Blynk.logEvent("high_water", "Water level below 20%. Irrigation OFF!");
  }
// Check for circuit disconnection (if sensor value is invalid, like 0)
  if (soilMoisturePercent == 0) {
    Blynk.logEvent("circuit_break", "Circuit Disconnected!"); // Notify user
    delay(1000);
  }
  
  // Run Blynk
  Blynk.run();

  delay(1000); // Small delay for stability
}
