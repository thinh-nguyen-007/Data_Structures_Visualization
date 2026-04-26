#pragma once
#include <string>
#include <vector>
#include "raylib.h"

class Sidepeak {
public:
    Sidepeak();
    ~Sidepeak();
    
    void InitFont();
    void SetCode(const std::vector<std::string>& code);
    
    // Draw the panel at the bottom right
    void Draw(int screenWidth, int screenHeight, const std::string& description, int activeLine);

private:
    std::vector<std::string> pseudoCode;
    Font codeFont;
    bool fontLoaded;
};
