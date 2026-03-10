#pragma once
#include <iostream> 
#include <raylib.h>
#include <sstream>

#include "../util/util.h"

class Alert
{
private:
	//Rectangle boundingBox;
	std::string heading;
	std::string subText;

	Vector2 subTextSize;
	float subTextFontSize = 30.0f;

	Color colorRect = WHITE;
	Color colorText = BLACK;

	Vector2 rectDim   = { 300.0f, 85.0f };
	Vector2 screenDim = {};
	Vector2 pos       = {};
	int alertBarWidth = rectDim.x - 20;
	

	float timer = 0.0f;
	float timerDuration = 2.0f;
public:
	Alert(std::string heading, std::string subText)
		: heading(heading)
	{
		this->subText = Util::WrapTextToWidth(subText, rectDim.x - 10, subTextFontSize);

		subTextSize = MeasureTextEx(
			Util::DefaultFont,
			this->subText.c_str(),
			subTextFontSize,
			0
		);

		int lineCount = 1;
		for (char c : this->subText)
		{
			if (c == '\n') lineCount++;
		}

		float lineHeight = subTextFontSize;
		float totalHeight = lineCount * lineHeight;

		rectDim.y += totalHeight;
	}

	void Show()
	{
		timer = timerDuration;
	}

	void Render()
	{
		
	}

	void Update(float dt)
	{
		screenDim = { GetScreenWidth() - 0.0f, GetScreenHeight() - 0.0f };
		pos = { screenDim.x - rectDim.x - 20.0f, 20.0f };
		Rectangle rect = { pos.x, pos.y, rectDim.x, rectDim.y };
		if (timer > 0)
		{
			DrawRectangle(rect.x, rect.y, rect.width, rect.height, BLACK);
			if (!CheckCollisionPointRec(GetMousePosition(), rect))
				timer -= dt;
			float barWidth = alertBarWidth * (timer / timerDuration);

			DrawRectangle(pos.x + 10, (pos.y + rectDim.y) - 20.0f, barWidth, 10, WHITE);
			DrawTextEx(Util::DefaultFont, heading.c_str(), { pos.x + 10.0f, pos.y + 10.0f }, 40, 0, WHITE);
			SetTextLineSpacing(-3);
			DrawTextEx(Util::DefaultFont, subText.c_str(), { pos.x + 10.0f, pos.y + 50.0f }, subTextFontSize, 0, WHITE);
		}
	}

	void SetSubText(std::string newSubText, float newHeight)
	{
		subText = newSubText;
		subText = Util::WrapTextToWidth(subText, rectDim.x - 10, subTextFontSize);

		rectDim.y = newHeight;
	}
};