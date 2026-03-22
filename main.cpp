#include "raylib.h"
#include "src/scenes/manager/Scenes.h"

int main() {
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);

    int heightOffset = 40;

    InitWindow(1920, 1080, "Queue Visualizer");
    Util::InitFonts();

    SceneManager Game;

    Game.PushScene(std::make_unique<QueueScene>());

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        Game.UpdateScene(dt);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        Game.RenderScene();
        

        EndDrawing();
    }

    CloseWindow();
}
