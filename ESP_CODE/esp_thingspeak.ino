#include <dummy.h>
#include <ESP8266WiFi.h>
const char* ssid = "*******";  
const char* password = "*****";  
const char* server = "api.thingspeak.com";
const char* apiKey = "*******";  
WiFiClient client;
void setup() {
    Serial.begin(9600);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to Wi-Fi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi connected.");
}
void loop() {
    if (Serial.available()) {
        String count = Serial.readStringUntil('\n');
        count.trim();  
        int numericCount = count.toInt();  
        if (numericCount !=0 || count == "0") {  
            Serial.print("Received Count: ");
            Serial.println(numericCount);
            sendDataToThingSpeak(String(numericCount));  
        } else {
            Serial.println("❌ Invalid Data: Only numeric values are allowed.");
        }
    }
    delay(16000); 
}

void sendDataToThingSpeak(String count) {
    if (client.connect(server, 80)) {
        Serial.println("Connected to ThingSpeak.");
        String url = "/update?api_key=" + String(apiKey) + "&field1=" + count;
        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: " + server + "\r\n" +
                     "Connection: close\r\n\r\n");
        unsigned long timeout = millis();
        while (client.connected() && millis() - timeout < 5000) {  
            if (client.available()) {
                String response = client.readString();
                Serial.println("ThingSpeak Response: " + response);      
                if (response.indexOf("Status: 200 OK") != -1) {
                    Serial.println("✔ Data successfully sent to ThingSpeak.");
                } else {
                    Serial.println("❌ Error sending data. Check API Key & Wi-Fi.");
                }
                break;
            }
        }
        client.stop();
    } else {
        Serial.println("❌ Failed to connect to ThingSpeak.");
    }
}
