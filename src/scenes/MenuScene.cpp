#include "./manager/Scenes.h"

SceneManager Game;

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

	b_exitGame.Draw();
}

void MenuScene::Update(float dt)
{

	b_arrayScene.OnClick([&]() {
		//std::cout << "Clicked";
		//Game.PopScene();
		Game.PushScene(std::make_unique<ArrayScene>());
	});

	b_linkListScene.OnClick([&]() {
		//Game.PopScene();
		Game.PushScene(std::make_unique<LinkListScene>());
	});
	b_stackScene.OnClick([&]() {
		//Game.PopScene();
		Game.PushScene(std::make_unique<StackScene>());
	});
	b_queueScene.OnClick([&]() {
		//Game.PopScene();
		Game.PushScene(std::make_unique<QueueScene>());
	});


	b_exitGame.OnClick([]() {
		CloseWindow();
	});

	c_menuItems.Update();
	b_exitGame.Update();
}

