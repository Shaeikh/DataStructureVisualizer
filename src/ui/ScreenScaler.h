#pragma once
#include "raylib.h"

class ScreenScaler {
private:
    int virtualWidth;
    int virtualHeight;

    float scaleX;
    float scaleY;
    float offsetX;
    float offsetY;
public:
    float scaleMin;
public:
    ScreenScaler(int vWidth, int vHeight)
        : virtualWidth(vWidth), virtualHeight(vHeight),
        scaleX(1.0f), scaleY(1.0f), scaleMin(1.0f),
        offsetX(0), offsetY(0) {
    }

    void update() {
        int w = GetScreenWidth();
        int h = GetScreenHeight();

        scaleX = (float)w / virtualWidth;
        scaleY = (float)h / virtualHeight;

        // keep aspect ratio
        scaleMin = (scaleX < scaleY) ? scaleX : scaleY;

        offsetX = (w - virtualWidth * scaleMin) / 2.0f;
        offsetY = (h - virtualHeight * scaleMin) / 2.0f;
    }

    Vector2 scaleVector(float x, float y) const {
        return Vector2{ x * scaleX, y * scaleY };
    }


    float scaleFloat(float value) const {
        return value * scaleMin;
    }

    void drawRect(float x, float y, float w, float h, Color color) const {
        Vector2 pos = scaleVector(x, y);
        DrawRectangle((int)pos.x, (int)pos.y,
            (int)scaleFloat(w), (int)scaleFloat(h),
            color);
    }

    void drawRectRounded(Rectangle rect, float roundeness, int segments, Color color) const {
        Vector2 pos = scaleVector(rect.x, rect.y);
        Vector2 dim = { scaleFloat(rect.width), scaleFloat(rect.height) };
        Rectangle modifiedRect = { pos.x, pos.y, dim.x, dim.y};

        DrawRectangleRounded(modifiedRect, roundeness, segments, color);
    }

    void drawText(Font font, const char* text, Vector2 position, float fontSize, Color color)
    {
        float spacing = fontSize / 10.0f;
        Vector2 pos = scaleVector(position.x, position.y);
        DrawTextEx(font, text, pos, fontSize, spacing, color);
    }

    void drawRectangleRoundedLines(Rectangle rect, float roundness, int segments, float lineThick, Color color)
    {
        Vector2 pos = scaleVector(rect.x, rect.y);
        Vector2 dim = { scaleFloat(rect.width), scaleFloat(rect.height) };
        Rectangle modifiedRect = { pos.x, pos.y, dim.x, dim.y };

        DrawRectangleRoundedLinesEx(modifiedRect, roundness, segments, lineThick, color);

    }

    void drawCircle(float x, float y, float radius, Color color) const {
        Vector2 pos = scaleVector(x, y);
        DrawCircle((int)pos.x, (int)pos.y, scaleFloat(radius), color);
    }


    void drawLine(float x1, float y1, float x2, float y2, Color color) const {
        Vector2 p1 = scaleVector(x1, y1);
        Vector2 p2 = scaleVector(x2, y2);
        DrawLine((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, color);
    }
};
