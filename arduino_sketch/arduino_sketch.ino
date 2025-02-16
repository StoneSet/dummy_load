#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <U8g2lib.h>

// Définition des broches
#define DS18B20_PIN 12  // Broche de la sonde DS18B20
#define LED_PIN 8       // LED témoin
#define RELAY_FAN_PIN 4 // Relais ventilateur
#define RELAY_PIN1 2    // Relais 1
#define RELAY_PIN2 3    // Relais 2

// Seuils de température
const float TEMP_THRESHOLD_FAN = 27.0;
const float TEMP_THRESHOLD_RELAY = 35.0;

// Résistances de charge
const float loadResistance4Ohms = 4.0;
const float loadResistance8Ohms = 8.0;

// Facteur du pont diviseur de tension
const float R8 = 76000.0;
const float R9 = 10000.0;
const float divFactor = (R8 + R9) / R9;

// Broches de mesure des tensions
const int voltagePin_L = A0;
const int voltagePin_R = A1;

// Objets pour la sonde DS18B20
OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

// Initialisation des écrans OLED en mode "Full Buffer"
U8G2_SSD1306_128X64_NONAME_F_HW_I2C display_L(U8G2_R0, U8X8_PIN_NONE);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C display_R(U8G2_R0, U8X8_PIN_NONE);

int lineHeight; // Hauteur d'une ligne

void setup() {
  Wire.begin();

  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_FAN_PIN, OUTPUT);
  pinMode(RELAY_PIN1, OUTPUT);
  pinMode(RELAY_PIN2, OUTPUT);

  digitalWrite(RELAY_FAN_PIN, LOW);
  digitalWrite(RELAY_PIN1, LOW);
  digitalWrite(RELAY_PIN2, LOW);

  sensors.begin();

  display_L.setI2CAddress(0x3C * 2);
  display_L.begin();
  display_R.setI2CAddress(0x3D * 2);
  display_R.begin();

  // Configuration des polices et récupération de la hauteur de ligne
  display_L.setFont(u8g2_font_ncenB08_tr);
  display_R.setFont(u8g2_font_ncenB08_tr);
  lineHeight = display_L.getMaxCharHeight();

  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  if (temperature >= TEMP_THRESHOLD_RELAY) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(RELAY_PIN1, HIGH);
    digitalWrite(RELAY_PIN2, HIGH);
    digitalWrite(RELAY_FAN_PIN, HIGH);
  } else if (temperature >= TEMP_THRESHOLD_FAN) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(RELAY_FAN_PIN, HIGH);
    digitalWrite(RELAY_PIN1, LOW);
    digitalWrite(RELAY_PIN2, LOW);
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(RELAY_FAN_PIN, LOW);
    digitalWrite(RELAY_PIN1, LOW);
    digitalWrite(RELAY_PIN2, LOW);
  }

  int rawVoltage_L = analogRead(voltagePin_L);
  int rawVoltage_R = analogRead(voltagePin_R);

  float voltage_L = (rawVoltage_L * 5.0 / 1023.0) * divFactor;
  float voltage_R = (rawVoltage_R * 5.0 / 1023.0) * divFactor;

  float power_L_4Ohms = (voltage_L * voltage_L) / loadResistance4Ohms;
  float power_L_8Ohms = (voltage_L * voltage_L) / loadResistance8Ohms;
  float power_R_4Ohms = (voltage_R * voltage_R) / loadResistance4Ohms;
  float power_R_8Ohms = (voltage_R * voltage_R) / loadResistance8Ohms;

  // === 🖥️ AFFICHAGE VOIE GAUCHE (Écran 0x3C) ===
  display_L.clearBuffer();
  display_L.setCursor(20, 10);  // Ajustement de la position du titre
  display_L.print("VOIE GAUCHE");

  display_L.setCursor(5, 25);
  display_L.print("P(4Ω): ");
  display_L.print(power_L_4Ohms, 2);
  display_L.print("W");

  display_L.setCursor(5, 40);
  display_L.print("P(8Ω): ");
  display_L.print(power_L_8Ohms, 2);
  display_L.print("W");

  display_L.sendBuffer();

  // === 🖥️ AFFICHAGE VOIE DROITE (Écran 0x3D) ===
  display_R.clearBuffer();
  display_R.setCursor(20, 10);  // Ajustement de la position du titre
  display_R.print("VOIE DROITE");

  display_R.setCursor(5, 25);
  display_R.print("P(4Ω): ");
  display_R.print(power_R_4Ohms, 2);
  display_R.print("W");

  display_R.setCursor(5, 40);
  display_R.print("P(8Ω): ");
  display_R.print(power_R_8Ohms, 2);
  display_R.print("W");

  display_R.sendBuffer();

  delay(1000);
}
