#pragma once
#include "raylib.h"
#include <string>
#include <iostream>
#include "../util/util.h"

class InputField
{
private:
    Rectangle bounds;
    std::string text;
    std::string placeholder;
    int maxLength;
    bool focused;

    float cursorTimer;
    bool showCursor;

    Color bgColor;
    Color borderColor;
    Color textColor;
    Color focusBorderColor;
    Color focusBgColor;

    Font font = Util::DefaultFont;

public:
    
    InputField(float width, float height, std::string placeholder, int maxLen = 32)
    {
        bounds = { 0.0f, 0.0f, width, height };
        maxLength = maxLen;
        text = "";
        focused = false;
        this->placeholder = placeholder;

        cursorTimer = 0.0f;
        showCursor = true;

        bgColor = WHITE;
        focusBgColor = BLACK;
        borderColor = BLACK;
        focusBorderColor = WHITE;
        textColor = WHITE;
    }

    void Layout(Vector2 position)
    {
        bounds.x = position.x;
        bounds.y = position.y;
    }

    void Update()
    {
        // Check mouse click for focus
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            focused = CheckCollisionPointRec(GetMousePosition(), bounds);
        }

        if (focused)
        {
            // Handle text input
            int key = GetCharPressed();
            while (key > 0)
            {
                if (((key >= 48) && (key <= 57) || (key == '-')) && text.length() < maxLength)
                {
                    if (key != '-' || text.size() == 0)
                    {
                        if (key == '-')
                            maxLength++;
                        text += (char)key;
                    }
                }
                key = GetCharPressed();
            }

            // Backspace
            if (IsKeyPressed(KEY_BACKSPACE) && !text.empty())
            {
                if (text.size() == 1 && text[0] == '-')
                    maxLength--;
                text.pop_back();
            }

            // Cursor blink
            cursorTimer += GetFrameTime();
            if (cursorTimer >= 0.5f)
            {
                showCursor = !showCursor;
                cursorTimer = 0.0f;
            }
        }
    }

    void Render()
    {
        // Background
        DrawRectangleRec(bounds, focused ? focusBgColor : bgColor);

        // Border
        DrawRectangleLinesEx(bounds, 3.0f,
            borderColor);

        // Text
        DrawTextEx(font, text.c_str(),
            { bounds.x + 10,
            bounds.y + bounds.height / 2 - 24 },
            50,
            0.0f,
            focused ? textColor : BLACK);

        // Placeholder
        DrawTextEx(font, placeholder.c_str(),
            { bounds.x + 10, focused || (text.size() > 0) ? 
            bounds.y - bounds.height / 2 - 10 :
            bounds.y + bounds.height / 2 - 20 },
            40,
            0.0f,
            focused || (text.size() > 0) ? BLACK : GRAY);

        // Cursor
        if (focused && showCursor)
        {
            int textWidth = MeasureTextEx(font, text.c_str(), 50, 0).x;
            int dummyTextWidth = MeasureTextEx(font, "0", 50, 0).x;

            //DrawLine(bounds.x + 14 + textWidth,
            //    bounds.y + 8,
            //    bounds.x + 14 + textWidth,
            //    bounds.y + bounds.height - 8,
            //    textColor);
            DrawRectangle(bounds.x + 12 + textWidth, bounds.y + bounds.height - 10, dummyTextWidth + 5, 4, WHITE);
        }
    }

    int GetText()
    {
        if (text.empty())
            return -9999;

        if (text == "-")
            return -9999;

        try
        {
            return std::stoi(text);
        }
        catch (const std::exception&)
        {
            return -9999;
        }
    }

    void SetText(const std::string& newText)
    {
        text = newText.substr(0, maxLength);
    }

    bool IsFocused() const
    {
        return focused;
    }
};