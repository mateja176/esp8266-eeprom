#include <Arduino.h>
#include <EEPROM.h>
#include <Ethernet.h>

const u_int CREDENTIALS_LENGTH = 16;

void parseCredentials(String credential, char chars[CREDENTIALS_LENGTH])
{
  credential.toCharArray(chars, CREDENTIALS_LENGTH);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Initialize EEPROM");

  EEPROM.begin(512);

  u_int address = 0;
  const u_int8_t ip1 = 0;
  EEPROM.put(address, ip1);
  address += 8;
  const u_int8_t ip2 = 0;
  EEPROM.put(address, ip2);
  address += 8;
  const u_int8_t ip3 = 0;
  EEPROM.put(address, ip3);
  address += 8;
  const u_int8_t ip4 = 0;
  EEPROM.put(address, ip4);
  address += 8;
  const String wifiSsid = "";
  char ssid[CREDENTIALS_LENGTH];
  parseCredentials(wifiSsid, ssid);
  EEPROM.put(address, ssid);
  address += sizeof(ssid);
  const String wifiPw = "";
  char pw[CREDENTIALS_LENGTH];
  parseCredentials(wifiPw, pw);
  EEPROM.put(address, pw);
  EEPROM.commit();
}

void loop()
{
  u_int address = 0;
  u_int8_t ip1 = 0;
  EEPROM.get(address, ip1);
  Serial.println("IP1: " + String(ip1));
  address += 8;
  u_int8_t ip2 = 0;
  EEPROM.get(address, ip2);
  Serial.println("IP2: " + String(ip2));
  address += 8;
  u_int8_t ip3 = 0;
  EEPROM.get(address, ip3);
  Serial.println("IP3: " + String(ip3));
  address += 8;
  u_int8_t ip4 = 0;
  EEPROM.get(address, ip4);
  Serial.println("IP4: " + String(ip4));
  if (ip1)
  {
    const IPAddress ip(ip1, ip2, ip3, ip4);
    Serial.println("ip: " + ip.toString());
  }
  address += 8;
  char ssid[CREDENTIALS_LENGTH];
  EEPROM.get(address, ssid);
  // * length returns the actual number of characters
  Serial.println("SSID: " + String(ssid) + ", size: " + String(sizeof(ssid)) + ", length: " + String(String(ssid).length()));
  address += sizeof(ssid);
  char pw[CREDENTIALS_LENGTH];
  EEPROM.get(address, pw);
  // * sizeof returns the size in bytes
  Serial.println("PW: " + String(pw) + ", size:" + String(sizeof(pw)) + ", length: " + String(String(pw).length()));
  if (String(ssid).length() && String(pw).length())
  {
    Serial.println("SSID+PW:" + String(ssid) + ", " + String(pw));
  }

  delay(1000);
}
