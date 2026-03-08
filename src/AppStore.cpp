#include "AppStore.h"
#include "UI.h"
#include "WiFiManager.h"

struct AppEntry {
    const char* name;
    const char* url;
    const char* filename;
};

const AppEntry appList[] = {
    {"Display Demo", "https://raw.githubusercontent.com/aoiastro/ESPMiniPhone/refs/heads/main/littlefs_files/scripts/test.cpp", "/app1.cpp"},
    {"RETURN", "", ""}
};
const int appCount = 2;

bool AppStore::downloadApp(const char* url, const char* filename) {
    if (!WiFiManager::isConnected()) {
        UI::showToast("No Wi-Fi", 0xe74c3c);
        return false;
    }

    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;

    UI::showToast("Downloading...", 0x3498db);

    if (http.begin(client, url)) {
        int httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK) {
            File file = LittleFS.open(filename, "w");
            if (file) {
                http.writeToStream(&file);
                file.close();
                UI::showToast("Download Success", 0x27ae60);
                http.end();
                return true;
            }
        }
        http.end();
    }
    UI::showToast("Download Failed", 0xe74c3c);
    return false;
}

void AppStore::executeApp(const char* filename) {
    File file = LittleFS.open(filename, "r");
    if (!file) {
        UI::showToast("File missing", 0xe74c3c);
        return;
    }

    M5.Lcd.fillScreen(0);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setFont(&fonts::Font0);
    M5.Lcd.setTextColor(0xFFFFFF);

    while (file.available()) {
        String line = file.readStringUntil('\n');
        line.trim();

        if (line.startsWith("M5.Lcd.fillScreen(")) {
            String val = line.substring(18, line.length() - 2);
            M5.Lcd.fillScreen(strtol(val.c_str(), NULL, 0));
        } 
        else if (line.startsWith("M5.Lcd.print(\"")) {
            String val = line.substring(14, line.lastIndexOf("\""));
            M5.Lcd.print(val);
        }
        else if (line.startsWith("M5.Lcd.println(\"")) {
            String val = line.substring(16, line.lastIndexOf("\""));
            M5.Lcd.println(val);
        }
        else if (line.startsWith("M5.Lcd.setTextColor(")) {
            String val = line.substring(20, line.length() - 2);
            M5.Lcd.setTextColor(strtol(val.c_str(), NULL, 0));
        }
        else if (line.startsWith("M5.Lcd.setCursor(")) {
            int firstComma = line.indexOf(',');
            String x = line.substring(17, firstComma);
            String y = line.substring(firstComma + 1, line.length() - 2);
            M5.Lcd.setCursor(x.toInt(), y.toInt());
        }
        else if (line.startsWith("delay(")) {
            String val = line.substring(6, line.length() - 2);
            delay(val.toInt());
        }
        
        M5.update();
        if (M5.BtnA.wasPressed() || M5.BtnB.wasPressed()) break;
    }
    
    file.close();
    UI::showToast("Execution Done", 0x3498db);
}

void AppStore::drawAppStore(int selectedApp, bool exists) {
    M5.Lcd.fillScreen(UI::COLOR_BG);
    UI::drawHeader("App Store", 0x8e44ad);
    
    for (int i = 0; i < appCount; i++) {
        int y = 40 + i * 45;
        uint32_t color = (i == selectedApp) ? 0x2980b9 : UI::COLOR_CARD;
        M5.Lcd.fillRoundRect(5, y, M5.Lcd.width() - 10, 40, 5, color);
        
        M5.Lcd.setTextColor(UI::COLOR_TEXT);
        M5.Lcd.setFont(&fonts::FreeSans9pt7b);
        M5.Lcd.setTextDatum(middle_left);
        M5.Lcd.drawString(appList[i].name, 15, y + 20);
        
        if (i < appCount - 1) {
            bool appExists = LittleFS.exists(appList[i].filename);
            M5.Lcd.setTextDatum(middle_right);
            M5.Lcd.setFont(&fonts::Font0);
            M5.Lcd.drawString(appExists ? "[Installed]" : "[Cloud]", M5.Lcd.width() - 15, y + 20);
        }
    }
    
    M5.Lcd.setTextColor(0x7f8c8d);
    M5.Lcd.setFont(&fonts::Font0);
    M5.Lcd.setTextDatum(bottom_center);
    M5.Lcd.drawString("B: Move / A: Decide", M5.Lcd.width()/2, M5.Lcd.height() - 5);
}

void AppStore::handleAppStore() {
    int selected = 0;
    while (true) {
        bool exists = (selected < appCount - 1) ? LittleFS.exists(appList[selected].filename) : false;
        drawAppStore(selected, exists);
        
        while (true) {
            M5.update();
            if (M5.BtnB.wasPressed()) { // Move
                selected = (selected + 1) % appCount;
                break;
            }
            if (M5.BtnA.wasPressed()) { // Decide
                if (selected == appCount - 1) return; // RETURN
                
                if (LittleFS.exists(appList[selected].filename)) {
                    executeApp(appList[selected].filename);
                } else {
                    if (downloadApp(appList[selected].url, appList[selected].filename)) {
                        executeApp(appList[selected].filename);
                    }
                }
                break;
            }
            delay(10);
        }
    }
}
