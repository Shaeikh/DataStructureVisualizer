#include "raylib.h"
#include "src/scenes/manager/Scenes.h"

#include "src/ui/Button.h"
#include "src/ui/Row.h"

int main() {
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);

    int heightOffset = 40;

    InitWindow(1920, 1080, "Array Visualizer");
    Util::InitFonts();
    std::cout << GetMonitorHeight(0) << std::endl;
    SceneManager Game;

    Game.PushScene(std::make_unique<ArrayScene>());

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        //int display = GetCurrentMonitor();
        //if (GetScreenWidth() != GetMonitorWidth(display) || GetScreenHeight() != GetMonitorHeight(display))
        //    SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));

        float dt = GetFrameTime();
        
        Game.UpdateScene(dt);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        Game.RenderScene();
        

        EndDrawing();
    }

    CloseWindow();
}
