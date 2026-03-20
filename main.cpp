#include "raylib.h"
#include "src/scenes/manager/Scenes.h"

#include "src/ui/Button.h"
#include "src/ui/Row.h"

int main() {
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);

    int heightOffset = 40;

    InitWindow(1920, 1080, "LinkList Visualizer");
    Util::InitFonts();

    SceneManager Game;

    Game.PushScene(std::make_unique<StackScene>());

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
