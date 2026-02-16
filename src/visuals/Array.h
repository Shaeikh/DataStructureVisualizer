#include "raylib.h"
#include <vector>
#include "../core/Events/EventBus.h"

class ArrayVisualizer : public IObserver {
public:
    void onEvent(const Event& e) override {
        lastEvent = e;
        highlightTimer = 0.5f;
    }

    void update(float dt) {
        if (highlightTimer > 0)
            highlightTimer -= dt;
    }

    void draw(const std::vector<int>& data) {
        int cellWidth = 60;
        int cellHeight = 60;
        int startX = 100;
        int y = 300;

        for (size_t i = 0; i < data.size(); i++) {
            Color color = LIGHTGRAY;

            if (highlightTimer > 0) {
                if (lastEvent.type == EventType::Insert && i == lastEvent.index)
                    color = GREEN;

                if (lastEvent.type == EventType::Erase && i == lastEvent.index)
                    color = RED;

                if (lastEvent.type == EventType::Update && i == lastEvent.index)
                    color = YELLOW;
            }

            DrawRectangle(startX + i * cellWidth, y, cellWidth - 5, cellHeight, color);
            DrawText(TextFormat("%d", data[i]),
                startX + i * cellWidth + 20,
                y + 20,
                20,
                BLACK);
        }
    }

private:
    Event lastEvent{};
    float highlightTimer = 0.0f;
};
