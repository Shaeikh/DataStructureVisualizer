#include "raylib.h"
#include "src/visuals/Array.h"
#include "src/core/DataStructures/Linear/Array.h"

int main() {

    InitWindow(1000, 600, "Array Visualizerr");

    EventBus bus;
    Array array(bus);
    ArrayVisualizer visualizer;

    bus.subscribe(&visualizer);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        float dt = GetFrameTime();

        // Input
        if (IsKeyPressed(KEY_ONE))
            array.Insert(0, GetRandomValue(1, 99));

        if (IsKeyPressed(KEY_TWO))
            array.Erase(0);

        if (IsKeyPressed(KEY_THREE))
            array.Update(0, GetRandomValue(100, 999));

        visualizer.update(dt);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        visualizer.draw(array.GetData());

        DrawText("1: Insert | 2: Remove | 3: Update | 4: Swap",
            20, 20, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
}
