#pragma once
#include <iostream>
#include <raylib.h>
#include <sstream>

namespace Util
{
    extern Font DefaultFont;

    void InitFonts();

    std::string WrapTextToWidth(const std::string& text, float maxWidth, float fontSize);

}