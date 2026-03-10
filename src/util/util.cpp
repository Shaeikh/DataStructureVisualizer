#include "util.h"
#include <raylib.h>
#include <sstream>

namespace Util
{
    Font DefaultFont;

    void InitFonts()
    {
        DefaultFont = LoadFontEx("assets/fonts/Whitestone.otf", 64, NULL, 0);

        if (DefaultFont.texture.id == 0)
        {
            std::cout << "Failed to load font\n";
        }
    }

    std::string WrapTextToWidth(const std::string& text, float maxWidth, float fontSize)
    {
        Font font = DefaultFont;
        float spacing = 0;

        std::stringstream ss(text);
        std::string word;
        std::string line;
        std::string result;

        while (ss >> word)
        {
            std::string testLine = line.empty() ? word : line + " " + word;
            Vector2 size = MeasureTextEx(font, testLine.c_str(), fontSize, spacing);

            if (size.x > maxWidth)
            {
                result += line + "\n";
                line = word;
            }
            else
            {
                line = testLine;
            }
        }

        result += line;
        return result;
    }
}