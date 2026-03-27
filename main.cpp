#include "raylib.h"
#include "src/scenes/manager/Scenes.h"
#include "src/ui/Button.h"

int main() {
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);

    int heightOffset = 40;

    InitWindow(1920, 1080, "Queue Visualizer");
    Util::InitFonts();

    
    SetExitKey(NULL);
    Game.PushScene(std::make_unique<MenuScene>());

    SetTargetFPS(60);

    Rectangle rect = {
        .x = 100,
        .y = 100,
        .width = 50,
        .height = 30
    };
    Button b = Button(rect, "Button", 50);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        //b.Update();
        Game.UpdateScene(dt);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        Game.RenderScene();
        //b.Draw();

        EndDrawing();
    }

    CloseWindow();
}
