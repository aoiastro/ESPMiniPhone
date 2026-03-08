#ifndef UI_H
#define UI_H

#include <M5Unified.h>

class UI {
public:
    static void begin();
    static void drawHomeScreen(int selectedIndex = 0);
    static void drawHeader(const char* title, uint32_t color);
    static void showToast(const char* message, uint32_t color = 0x3498db);
    static void drawButton(int x, int y, int w, int h, const char* label, uint32_t color, bool pressed = false);
    
    // Theme Colors
    static const uint32_t COLOR_BG = 0x000000;
    static const uint32_t COLOR_ACCENT = 0x3498db;
    static const uint32_t COLOR_TEXT = 0xFFFFFF;
    static const uint32_t COLOR_CARD = 0x1c1c1e;
};

#endif
