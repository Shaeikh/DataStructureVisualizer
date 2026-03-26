#include "./manager/Scenes.h"

void MenuScene::Render()
{
	//DrawTexture(logo, (GetScreenWidth() - logo.width) / 2, (GetScreenHeight() - logo.height) / 2, RAYWHITE);
	DrawTextureEx(
		logo, 
		{ 
			(GetScreenWidth() - (logo.width * 0.4f)) / 2.0f,
			100
		}, 
		0.0f, 
		0.4f, 
		RAYWHITE
	);

	c_menuItems.Layout({ (GetScreenWidth() - b_arrayScene.GetWidth()) / 2.0f, 450.0f });
	c_menuItems.Render();
}

void MenuScene::Update(float dt)
{
	c_menuItems.Update();
}

