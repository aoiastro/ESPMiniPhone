#ifndef APPSTORE_H
#define APPSTORE_H

#include <M5Unified.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <LittleFS.h>

class AppStore {
public:
    static bool downloadApp(const char* url, const char* filename);
    static void executeApp(const char* filename);
    static void drawAppStore(int selectedApp, bool exists);
    static void handleAppStore();
};

#endif
