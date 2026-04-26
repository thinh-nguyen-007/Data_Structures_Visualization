#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include "DrawText.h"
#include "raylib.h"
#include "raymath.h"
#include "Textures.h"

using namespace std;

void DrawGlowText(Font FONT, const char* text, Vector2 position, int fontSize, int spacing, Color glowColor, Color textColor) {
    //DrawTextEx(FONT, text, position, fontSize, spacing, textColor);

    float x = position.x;
    float TextWidth = 0.0f;

    for (int i = 0; text[i] != '\0'; i++) {
        TextWidth += MeasureTextEx(FONT, TextFormat("%c", text[i]), (float)fontSize, (float)spacing).x;
    }   

    x += (MeasureTextEx(FONT, text, (float)fontSize, (float)spacing).x - TextWidth) / 2;

    for (int i = 0; text[i] != '\0'; i++)
    {
        // Current character as string
        char ch[2] = { text[i], '\0' };

        // Measure character size properly
        Vector2 size = MeasureTextEx(FONT, ch, (float)fontSize, (float)spacing);

        // 🔥 Glow (multi-layer for smoother effect)
        for (int layer = 1; layer <= 3; layer++)
        {
            int offset = layer * 2;
            float alpha = 0.15f / layer; // fade out layers

            for (int dx = -offset; dx <= offset; dx++)
            {
                for (int dy = -offset; dy <= offset; dy++)
                {
                    if (dx == 0 && dy == 0) continue;

                    DrawTextEx(
                        FONT,
                        ch,
                        (Vector2){ x + dx, position.y + dy },
                        (float)fontSize,
                        (float)spacing,
                        Fade(glowColor, alpha)
                    );
                }
            }
        }

        // ✨ Main character (sharp)
        DrawTextEx(
            FONT,
            ch,
            (Vector2){ x, position.y },
            (float)fontSize,
            (float)spacing,
            textColor
        );

        // Move to next character
        x += size.x;
    }
}

void DrawNormalText(Font FONT, const char* text, Vector2 position, int fontSize, int spacing, Color textColor) {
    for (int i = 0; text[i] != '\0'; i++)
    {
        char c = text[i];

        int index = GetGlyphIndex(MyFont, c);
        GlyphInfo glyph = MyFont.glyphs[index];

        if (c == ' ')
        {
            position.x += MeasureTextEx(MyFont, " ", (float)fontSize, (float)spacing).x + spacing + 2;
            continue;
        }

        const char* letter = TextFormat("%c", c);

        DrawTextEx(FONT, letter, position, (float)fontSize, (float)spacing, textColor);

        Vector2 size = MeasureTextEx(FONT, letter, (float)fontSize, (float)spacing);

        position.x += glyph.advanceX * fontSize / MyFont.baseSize + spacing;
    }
}