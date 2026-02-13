#include "scenes/manager/scenes.h"

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "DSA Visualizer");

	SetTargetFPS(60);

	SceneManager Game;
	Game.PushScene(std::make_unique<ArrayScene>());

	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		BeginDrawing();

		ClearBackground(RAYWHITE);

		Game.RenderScene();
		Game.UpdateScene(dt);


		EndDrawing();
	}

	CloseWindow();

	return 0;
}