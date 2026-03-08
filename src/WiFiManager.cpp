#include "WiFiManager.h"
#include <ESPmDNS.h>
#include "UI.h"

String WiFiManager::_ssid = "";
String WiFiManager::_password = "";
WebServer WiFiManager::_server(80);
DNSServer WiFiManager::_dnsServer;
bool WiFiManager::_portalRunning = false;

bool WiFiManager::begin() {
    if (!LittleFS.begin(true)) {
        Serial.println("LittleFS Mount Failed");
        return false;
    }
    loadSettings();
    return true;
}

void WiFiManager::loadSettings() {
    if (LittleFS.exists("/wifi.txt")) {
        File file = LittleFS.open("/wifi.txt", "r");
        if (file) {
            _ssid = file.readStringUntil('\n');
            _password = file.readStringUntil('\n');
            _ssid.trim();
            _password.trim();
            file.close();
        }
    }
}

void WiFiManager::saveSettings(const String& ssid, const String& password) {
    File file = LittleFS.open("/wifi.txt", "w");
    if (file) {
        file.println(ssid);
        file.println(password);
        file.close();
        _ssid = ssid;
        _password = password;
    }
}

bool WiFiManager::autoConnect() {
    if (_ssid == "") return false;

    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid.c_str(), _password.c_str());

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 50000) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi Connected");
        return true;
    } else {
        Serial.println("\nWiFi Connection Timeout");
        return false;
    }
}

void WiFiManager::startConfigPortal() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP("ESPMiniPhone-Config");
    
    _dnsServer.start(53, "*", WiFi.softAPIP());
    
    if (MDNS.begin("m5")) {
        MDNS.addService("http", "tcp", 80);
    }

    _server.on("/", handleRoot);
    _server.on("/save", HTTP_POST, handleSave);
    _server.onNotFound(handleNotFound);
    _server.begin();
    
    _portalRunning = true;
    Serial.println("Config Portal Started. Connect to ESPMiniPhone-Config");
}

void WiFiManager::handleRoot() {
    String html = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<style>body{font-family:sans-serif; background:#121212; color:white; padding:20px;}";
    html += "input{width:100%; padding:10px; margin:10px 0; border:none; border-radius:5px;}";
    html += "button{width:100%; padding:10px; background:#3498db; color:white; border:none; border-radius:5px;}</style></head><body>";
    html += "<h1>ESPMiniPhone Config</h1>";
    html += "<form action='/save' method='POST'>";
    html += "SSID:<br><input type='text' name='ssid' value='" + _ssid + "'><br>";
    html += "Password:<br><input type='password' name='password'><br>";
    html += "<button type='submit'>Save & Connect</button></form></body></html>";
    _server.send(200, "text/html", html);
}

void WiFiManager::handleSave() {
    if (_server.hasArg("ssid") && _server.hasArg("password")) {
        saveSettings(_server.arg("ssid"), _server.arg("password"));
        _server.send(200, "text/html", "Settings Saved. Restarting...");
        delay(2000);
        ESP.restart();
    } else {
        _server.send(400, "text/plain", "Bad Request");
    }
}

void WiFiManager::handleNotFound() {
    _server.sendHeader("Location", "/", true);
    _server.send(302, "text/plain", "");
}

void WiFiManager::loop() {
    if (_portalRunning) {
        _dnsServer.processNextRequest();
        _server.handleClient();
    }
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}
