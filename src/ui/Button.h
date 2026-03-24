#pragma once

#include <iostream>
#include <raylib.h>
#include <functional>

#include "ScreenScaler.h"
#include "Constants.h"

#include "../util/util.h"

class Button
{
private:
	Rectangle boundingBox;
	std::string text;
	float fontSize;
	Color colorRect = WHITE;
	Color colorText = BLACK;
	Vector2 textSize;
	//ScreenScaler scaler = ScreenScaler(UI::V_SCREEN_WIDTH, UI::V_SCREEN_HEIGHT);

	Font font = Util::DefaultFont;

public:
	Button(Rectangle bb, const std::string &text, float fs)
		: boundingBox(bb), text(text), fontSize(fs) {

		textSize = MeasureTextEx(font, text.c_str(), fontSize, 0);
		float paddingX = 20.0f;
		float paddingY = 10.0f;

		boundingBox.width = textSize.x + paddingX * 2.5;
		boundingBox.height = textSize.y + paddingY * 2.5;

	}

	void Draw()
	{
		float roundness = 0.6f;
		DrawRectanglePro(boundingBox, {0, 0}, 0.0f, colorRect);
		//DrawRectanglePro(boundingBox, colorRect);
		DrawTextEx(font,
			text.c_str(),
			{
				boundingBox.x + (boundingBox.width - textSize.x) / 2.0f,
				boundingBox.y + (boundingBox.height - textSize.y) / 2.0f
			},
			fontSize,
			0.0f,
			colorText);
		DrawRectangleLinesEx(boundingBox, 4.0f, BLACK);

		float paddingX = 20.0f;
		float paddingY = 10.0f;

		//boundingBox.width = textSize.x + paddingX * 2.5;
		//boundingBox.height = textSize.y + paddingY * 2.5;

		DrawTriangle(
			Vector2{
				boundingBox.x,
				boundingBox.y
			},
			Vector2{
				boundingBox.x,
				boundingBox.y + 15 * textSize.y * 0.03f
			},
			Vector2{
				boundingBox.x + 15.0f * textSize.y * 0.03f,
				boundingBox.y
			},

			RAYWHITE
		);

		DrawLineEx(
			{
				boundingBox.x + 15.0f * textSize.y * 0.03f,
				boundingBox.y + 2.0f
			},
			{
				boundingBox.x + 2.0f,
				boundingBox.y + 15 * textSize.y * 0.03f
			},
			4.0f,
			BLACK
		);

		DrawTriangle(
			Vector2{
				boundingBox.x + boundingBox.width - 15.0f * textSize.y * 0.03f,
				boundingBox.y
			},
			Vector2{
				boundingBox.x + boundingBox.width,
				boundingBox.y + 15 * textSize.y * 0.03f
			},
			Vector2{
				boundingBox.x + boundingBox.width,
				boundingBox.y
			},
			
			RAYWHITE
		);

		DrawLineEx(
			{
				boundingBox.x + boundingBox.width - 15.0f * textSize.y * 0.03f,
				boundingBox.y + 2.0f
			},
			{
				boundingBox.x + boundingBox.width - 2.0f,
				boundingBox.y + 15 * textSize.y * 0.03f
			},
			4.0f,
			BLACK
		);

		DrawTriangle(
			Vector2{
				boundingBox.x,
				boundingBox.y + boundingBox.height
			},
			Vector2{
				boundingBox.x + 15 * textSize.y * 0.03f,
				boundingBox.y + boundingBox.height
			},
			Vector2{
				boundingBox.x,
				boundingBox.y + boundingBox.height - 15.0f * textSize.y * 0.03f
			},
			RAYWHITE
		);

		DrawLineEx(
			{
				boundingBox.x + 2.0f,
				boundingBox.y + boundingBox.height - 15.0f * textSize.y * 0.03f
			},
			{
				boundingBox.x + 15 * textSize.y * 0.03f,
				boundingBox.y + boundingBox.height - 2.0f
			},
			4.0f,
			BLACK
		);

		DrawTriangle(
			Vector2{
				boundingBox.x + boundingBox.width,
				boundingBox.y + boundingBox.height
			},
			Vector2{
				boundingBox.x + boundingBox.width,
				boundingBox.y + boundingBox.height - 15.0f * textSize.y * 0.03f
			},
			Vector2{
				boundingBox.x + boundingBox.width - 15 * textSize.y * 0.03f,
				boundingBox.y + boundingBox.height
			},
			RAYWHITE
		);

		DrawLineEx(
			{
				boundingBox.x + boundingBox.width - 2.0f,
				boundingBox.y + boundingBox.height - 15.0f * textSize.y * 0.03f
			},
			{
				boundingBox.x + boundingBox.width - 15 * textSize.y * 0.03f,
				boundingBox.y + boundingBox.height - 2.0f
			},
			4.0f,
			BLACK
		);

		//Vector2 screenPos = scaler.scaleVector(boundingBox.x, boundingBox.y);

		//scaler.drawRectRounded(boundingBox, roundness, 255, colorRect);
		//scaler.drawText(GetFontDefault(),
		//	text.c_str(),
		//	{
		//		boundingBox.x + (boundingBox.width - textSize.x) / 2.0f,
		//		boundingBox.y + (boundingBox.height - textSize.y) / 2.0f
		//	},
		//	fontSize,
		//	colorText);
		//scaler.drawRectangleRoundedLines(boundingBox, roundness, 255, 5.0f, BLACK);
	}

	void Update()
	{
		if (isHovering())
		{
			colorText = WHITE;
			colorRect = BLACK;
		}
		else
		{
			colorText = BLACK;
			colorRect = WHITE;
		}
	}

	void OnClick(std::function<void()> callback)
	{
		if (isHovering() && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			callback();			
	}

	void SetPosition(Vector2 position)
	{
		boundingBox.x = position.x;
		boundingBox.y = position.y;
	}

	float GetWidth() const
	{
		return boundingBox.width;
	}

	float GetHeight() const
	{
		return boundingBox.height;
	}

	Rectangle GetBounds() const
	{
		return boundingBox;
	}

private:
	bool isHovering()
	{
		return CheckCollisionPointRec(GetMousePosition(), boundingBox);
	}
};