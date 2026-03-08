#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <LittleFS.h>

class WiFiManager {
public:
    static bool begin();
    static bool autoConnect();
    static void startConfigPortal();
    static void loop();
    static bool isConnected();
    static void resetSettings();

private:
    static void loadSettings();
    static void saveSettings(const String& ssid, const String& password);
    static void handleRoot();
    static void handleSave();
    static void handleNotFound();
    
    static String _ssid;
    static String _password;
    static WebServer _server;
    static DNSServer _dnsServer;
    static bool _portalRunning;
};

#endif
