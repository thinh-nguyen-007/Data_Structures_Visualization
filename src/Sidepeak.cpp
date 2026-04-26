#include "Sidepeak.h"

Sidepeak::Sidepeak() : fontLoaded(false) {}

Sidepeak::~Sidepeak() {
  if (fontLoaded) {
    UnloadFont(codeFont);
  }
}

void Sidepeak::SetFont(Font codeF, Font descF) {
  codeFont = codeF;
  descFont = descF;
  fontLoaded = true;
}

void Sidepeak::SetCode(const std::vector<std::string> &code) {
  pseudoCode = code;
}

void Sidepeak::Draw(int screenWidth, int screenHeight,
                    const std::string &description, int activeLine) {
  int panelWidth = 600; // <--- Edit this to change the width of the whole panel
  int codeLineHeight = 30;
  int descriptionHeight =
      55; // <--- Edit this to change the height of the cyan part
  int codeHeight = pseudoCode.size() * codeLineHeight + 20;
  int panelHeight = descriptionHeight + codeHeight;
  int startX = screenWidth - panelWidth - 20;
  int startY = screenHeight - panelHeight - 20;

  // Draw description background (cyan-like)
  Color descBg = {64, 180, 196, 255};
  DrawRectangle(startX, startY, panelWidth, descriptionHeight, descBg);

  // Draw description text (bold, slightly bigger than pseudo code)
  if (fontLoaded) {
    DrawTextEx(descFont, description.c_str(),
               {(float)startX + 20, (float)startY + 8}, 23, 1, WHITE);
  } else {
    DrawText(description.c_str(), startX + 10, startY + 10, 20, WHITE);
  }

  // Draw code background (greenish)
  Color codeBg = {160, 200, 60, 255};
  int codeStartY = startY + descriptionHeight;
  DrawRectangle(startX, codeStartY, panelWidth, codeHeight, codeBg);

  // Draw code lines
  for (size_t i = 0; i < pseudoCode.size(); i++) {
    int y = codeStartY + 10 + i * codeLineHeight;

    // Highlight active line (1-indexed)
    if ((int)i + 1 == activeLine) {
      DrawRectangle(startX, y - 2, panelWidth, codeLineHeight, BLACK);
      if (fontLoaded) {
        DrawTextEx(descFont, pseudoCode[i].c_str(),
                   {(float)startX + 15, (float)y}, 24, 1, WHITE);
      } else {
        DrawText(pseudoCode[i].c_str(), startX + 15, y, 20, WHITE);
      }
    } else {
      if (fontLoaded) {
        DrawTextEx(descFont, pseudoCode[i].c_str(),
                   {(float)startX + 15, (float)y}, 24, 1, BLACK);
      } else {
        DrawText(pseudoCode[i].c_str(), startX + 15, y, 20, BLACK);
      }
    }
  }
}
