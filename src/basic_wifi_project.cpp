#ifdef BASIC_WIFI_PROJECT
#include <Arduino.h>
#include<WiFi.h>

// Replace with your network credentials
const char* ssid = "Den";
const char* password = "denzaza555";

WiFiServer server(80);  // Port 80 for HTTP
int ledPin = 2;         // GPIO 4 for LED


void runSetup() {
    Serial.begin(115200);
    Serial.println("FLAG: BASIC_WIFI_PROJECT");
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  // Your web server address

    server.begin();

}

void runLoop() {
    WiFiClient client = server.available();   // Listen for incoming clients

    if (client) {
    Serial.println("New Client Connected.");
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    // Control LED
    if (request.indexOf("/LED=ON") != -1) {
        digitalWrite(ledPin, HIGH);
    } else if (request.indexOf("/LED=OFF") != -1) {
        digitalWrite(ledPin, LOW);
    }

    // Build Web Page
    String html = "<!DOCTYPE html><html>";
    html += "<head><meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<title>ESP32 LED Control</title></head>";
    html += "<body style='text-align:center; font-family:sans-serif;'>";
    html += "<h2>ESP32 Web LED Controller</h2>";
    html += "<p><a href='/LED=ON'><button style='padding:10px 20px; background:green; color:white; border:none;'>TURN ON</button></a></p>";
    html += "<p><a href='/LED=OFF'><button style='padding:10px 20px; background:red; color:white; border:none;'>TURN OFF</button></a></p>";
    html += "</body></html>";

    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
    client.println(html);
    client.stop();
    Serial.println("Client disconnected.");
    }
}
#endif
