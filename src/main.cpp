#include <Arduino.h>
#include <U8g2lib.h>
#include <WiFi.h>
#include <Wire.h>

#if __has_include("secrets.h")
#include "secrets.h"
#endif

#ifndef WIFI_SSID
#define WIFI_SSID ""
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD ""
#endif

namespace {

constexpr uint8_t kSdaPin = 21;
constexpr uint8_t kSclPin = 22;
constexpr uint8_t kDefaultOledAddress = 0x3C;
constexpr uint32_t kConnectTimeoutMs = 20000;
constexpr uint32_t kRetryIntervalMs = 30000;
constexpr uint32_t kScreenRefreshMs = 500;

// The Robocraze listing identifies SSD1315 in its description and SSD1306
// elsewhere. Its four-pin I2C module is commonly driven with the SSD1306
// command set. If the screen stays blank, verify the controller/address.
U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);

uint8_t oledAddress = kDefaultOledAddress;
uint32_t lastConnectAttemptMs = 0;
uint32_t lastScreenRefreshMs = 0;
wl_status_t lastStatus = WL_IDLE_STATUS;
String lastIp;

bool hasWifiCredentials() {
  return WIFI_SSID[0] != '\0' && WIFI_PASSWORD[0] != '\0' &&
         String(WIFI_SSID) != "YOUR_WIFI_NAME" &&
         String(WIFI_PASSWORD) != "YOUR_WIFI_PASSWORD";
}

uint8_t findOledAddress() {
  constexpr uint8_t candidates[] = {0x3C, 0x3D};
  for (const uint8_t address : candidates) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      return address;
    }
  }
  return kDefaultOledAddress;
}

void drawMessage(const char* title, const char* line1, const char* line2) {
  display.clearBuffer();
  display.setFont(u8g2_font_6x10_tf);
  display.drawStr(0, 10, title);
  display.drawHLine(0, 14, 128);
  display.setFont(u8g2_font_7x14B_tf);
  display.drawStr(0, 34, line1);
  display.setFont(u8g2_font_6x10_tf);
  display.drawStr(0, 52, line2);
  display.sendBuffer();
}

void drawConnectedScreen() {
  const String ip = WiFi.localIP().toString();
  if (lastStatus == WL_CONNECTED && ip == lastIp &&
      millis() - lastScreenRefreshMs < 5000) {
    return;
  }

  display.clearBuffer();
  display.setFont(u8g2_font_6x10_tf);
  display.drawStr(0, 10, "ESP32 Wi-Fi status");
  display.drawHLine(0, 14, 128);
  display.setFont(u8g2_font_7x14B_tf);
  display.drawStr(0, 34, "Connected");
  display.setFont(u8g2_font_6x10_tf);
  display.drawStr(0, 52, "IP:");
  display.drawStr(18, 52, ip.c_str());
  display.sendBuffer();

  lastStatus = WL_CONNECTED;
  lastIp = ip;
  lastScreenRefreshMs = millis();
}

void beginWifiConnection() {
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  lastConnectAttemptMs = millis();
  lastStatus = WL_IDLE_STATUS;
  Serial.println("Connecting to configured Wi-Fi...");
}

}  // namespace

void setup() {
  Serial.begin(115200);
  Wire.begin(kSdaPin, kSclPin);

  oledAddress = findOledAddress();
  display.setI2CAddress(static_cast<uint8_t>(oledAddress << 1));
  display.begin();

  if (!hasWifiCredentials()) {
    drawMessage("ESP32 Wi-Fi status", "Add Wi-Fi details", "include/secrets.h");
    Serial.println("Create include/secrets.h from secrets.example.h.");
    return;
  }

  drawMessage("ESP32 Wi-Fi status", "Connecting...", "Please wait");
  beginWifiConnection();
}

void loop() {
  if (!hasWifiCredentials()) {
    delay(1000);
    return;
  }

  const uint32_t now = millis();
  const wl_status_t status = WiFi.status();

  if (status == WL_CONNECTED) {
    drawConnectedScreen();
    delay(50);
    return;
  }

  // Remember that we left the connected state so a reconnect redraws
  // immediately, even when the assigned IP address stays the same.
  lastStatus = status;

  if (now - lastScreenRefreshMs >= kScreenRefreshMs) {
    if (now - lastConnectAttemptMs < kConnectTimeoutMs) {
      drawMessage("ESP32 Wi-Fi status", "Connecting...", "Please wait");
    } else {
      drawMessage("ESP32 Wi-Fi status", "Not connected", "Retrying...");
    }
    lastScreenRefreshMs = now;
  }

  if (now - lastConnectAttemptMs >= kRetryIntervalMs) {
    beginWifiConnection();
  }

  delay(50);
}
