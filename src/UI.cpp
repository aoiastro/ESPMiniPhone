#include "UI.h"

void UI::begin() {
    M5.Lcd.setRotation(0); // Portrait
    M5.Lcd.fillScreen(COLOR_BG);
    drawHomeScreen();
}

void UI::drawHeader(const char* title, uint32_t color) {
    M5.Lcd.fillRect(0, 0, M5.Lcd.width(), 24, color);
    M5.Lcd.setTextColor(COLOR_TEXT);
    M5.Lcd.setTextDatum(top_center);
    M5.Lcd.setFont(&fonts::FreeSansBold9pt7b);
    M5.Lcd.drawString(title, M5.Lcd.width() / 2, 4);
}

void UI::drawHomeScreen(int selectedIndex) {
    M5.Lcd.fillScreen(COLOR_BG);
    drawHeader("ESPMiniPhone", COLOR_ACCENT);
    
    // Wi-Fi Connection Button
    drawButton(10, 40, 115, 60, "Wi-Fi\nConnection", 0x27ae60, selectedIndex == 0);
    
    // App Store Button
    drawButton(10, 110, 115, 60, "App Store", 0x8e44ad, selectedIndex == 1);
    
    // Info area
    M5.Lcd.setFont(&fonts::Font0);
    M5.Lcd.setTextColor(0x7f8c8d);
    M5.Lcd.setTextDatum(bottom_center);
    M5.Lcd.drawString("M5StickC Plus2", M5.Lcd.width() / 2, M5.Lcd.height() - 5);
}

void UI::drawButton(int x, int y, int w, int h, const char* label, uint32_t color, bool pressed) {
    uint32_t drawColor = pressed ? (color & 0x7F7F7F) : color;
    M5.Lcd.fillRoundRect(x, y, w, h, 8, drawColor);
    M5.Lcd.drawRoundRect(x, y, w, h, 8, COLOR_TEXT);
    
    M5.Lcd.setTextColor(COLOR_TEXT);
    M5.Lcd.setTextDatum(middle_center);
    M5.Lcd.setFont(&fonts::FreeSans9pt7b);
    M5.Lcd.drawString(label, x + w / 2, y + h / 2);
}

void UI::showToast(const char* message, uint32_t color) {
    int h = 30;
    int y = M5.Lcd.height() - h - 20;
    M5.Lcd.fillRoundRect(5, y, M5.Lcd.width() - 10, h, 5, color);
    M5.Lcd.setTextColor(COLOR_TEXT);
    M5.Lcd.setTextDatum(middle_center);
    M5.Lcd.setFont(&fonts::Font0);
    M5.Lcd.drawString(message, M5.Lcd.width() / 2, y + h / 2);
    delay(1500);
}
