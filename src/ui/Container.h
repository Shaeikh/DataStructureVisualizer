#pragma once

#include <raylib.h>
#include <iostream>

#include "../util/util.h"

class Container
{
public:
	Container(std::string title, Rectangle rect, float roundness = 0.2, Color lineColor = BLACK)
		: title(title), rect(rect), roundness(roundness), lineColor(lineColor)
	{};

	void Render()
	{
		DrawRectangleRoundedLinesEx(rect, roundness, 255, 4, lineColor);

		Vector2 textSize = MeasureTextEx(font, title.c_str(), fontSize, 0);
		DrawRectangle(rect.x + 35, rect.y - 20, textSize.x + 10, textSize.y, RAYWHITE);
		
		DrawTextEx(font, title.c_str(), { rect.x + 40.0f, rect.y - (fontSize / 2.0f) }, fontSize, 0, lineColor);

	}

private:
	std::string title;
	Font font = Util::DefaultFont;

	int fontSize = 40;

	Rectangle rect;
	Color lineColor;
	float roundness;
};