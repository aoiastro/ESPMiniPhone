#include <M5Unified.h>
#include "UI.h"
#include "WiFiManager.h"
#include "AppStore.h"

int selectedIndex = 0;

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    Serial.begin(115200);

    UI::begin();

    if (WiFiManager::begin()) {
        UI::showToast("Connecting WiFi...", UI::COLOR_ACCENT);
        if (WiFiManager::autoConnect()) {
            UI::showToast("WiFi Connected", 0x27ae60);
        } else {
            UI::showToast("WiFi Timeout", 0xe74c3c);
        }
    }

    UI::drawHomeScreen(selectedIndex);
}

void loop() {
    M5.update();
    WiFiManager::loop();

    if (M5.BtnB.wasPressed()) { // Side button - Change focus (Move)
        selectedIndex = (selectedIndex + 1) % 2;
        UI::drawHomeScreen(selectedIndex);
    }

    if (M5.BtnA.wasPressed()) { // Front button - Select (Decide)
        if (selectedIndex == 0) {
            UI::showToast("Starting AP Mode", 0x27ae60);
            WiFiManager::startConfigPortal();
            UI::showToast("m5.local\nPortal Active", 0x3498db);
        } else if (selectedIndex == 1) {
            AppStore::handleAppStore();
            UI::drawHomeScreen(selectedIndex);
        }
    }

    delay(10);
}
