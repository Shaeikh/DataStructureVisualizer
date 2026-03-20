#include "raylib.h"
#include <deque>
#include <queue>

#include "../core/Events/EventBus.h"

#include "../util/util.h"

class StackVisualizer : public IObserver {
public:
    void OnEvent(const Event& e) override {
        // Insert/Erase/Update will animate immediately no delay
        while (!eventQueue.empty())
            eventQueue.pop();

        currentEvent = e;
        highlightTimer = 0.5f;
    }

    void Update(float dt) {
        if (highlightTimer > 0)
            highlightTimer -= dt;

        if (highlightTimer <= 0 && !eventQueue.empty()) {
            currentEvent = eventQueue.front();
            //std::cout << currentEvent.value << std::endl;
            eventQueue.pop();
            highlightTimer = 0.3f;
        }
    }

    void Render(const std::deque<int>& data) {
        int cellWidth = 60;
        int cellHeight = 60;
        int startX = 40;
        int y = 300;

        // Stack container for containing all the elements
            //Container containerVisualization = Container("Visualization", Rectangle{ 20, 260.0f, GetScreenWidth() - 540.0f, GetScreenHeight() - 280.0f }, 0.05f);

        int containerWidth = 280;
        int containerHeight = 500;
        float containerX = 20 + (GetScreenWidth() - 540.0f - containerWidth) / 2;
        float containerY = 280;
        Rectangle stackContainerRect = {
            containerX,
            containerY,
            containerWidth,
            containerHeight
        };
        DrawRectangleLinesEx(
            stackContainerRect,
            4.0f,
            BLACK
        );

        for (size_t i = 0; i < data.size(); i++)
        {
            Color color = WHITE;

            if (highlightTimer > 0) {
                if (currentEvent.type == EventType::Push && i == currentEvent.index)
                    color = GREEN;

                if (currentEvent.type == EventType::Pop && i == currentEvent.index)
                    color = RED;

                if (currentEvent.type == EventType::Update && i == currentEvent.index)
                    color = PURPLE;
            }
            

            Rectangle rect = {
                containerX,
                containerY + containerHeight - cellHeight - (cellHeight - 4) * i,
                containerWidth,
                cellHeight
            };

            //DrawRectangleProRounded(
            //    rect, {}, 0,
            //    color
            //);

            DrawRectangleLinesEx(
                rect,
                4.0f,
                BLACK
            );
            int fontSize = 30;
            const char* valueText = TextFormat("%d", data[i]);
            Vector2 textSize = MeasureTextEx(font, valueText, fontSize, 0);

            DrawTextEx(
                font,
                valueText,
                { 
                    containerX + (containerWidth - textSize.x) / 2,
                    containerY + containerHeight - cellHeight - (cellHeight - 4) * i
                },
                fontSize,
                0,
                BLACK
            );

            //DrawTextEx(
            //    font,
            //    TextFormat("%d", i),
            //    { startX + i * cellWidth + 22 - 0.0f,
            //    y + 70 - 0.0f },
            //    fontSize,
            //    0,
            //    GRAY
            //);

            // Search not needed for stack
            //if (currentEvent.type == EventType::Search)
            //{
            //    if (eventQueue.empty())
            //        DrawTextEx(
            //            font,
            //            "Search Result",
            //            { (float)startX,
            //            y + 120.0f },
            //            50,
            //            0,
            //            DARKGRAY
            //        );

            //    if (currentEvent.targetValue == data[i] && eventQueue.empty())
            //    {
            //        DrawTextEx(
            //            font,
            //            TextFormat("'%d' is at index [%d]", currentEvent.value, currentEvent.index),
            //            { startX + 0.0f,
            //            y + 165.0f },
            //            40,
            //            0,
            //            BLACK
            //        );
            //    }
            //    else if (currentEvent.index == i && eventQueue.empty() && currentEvent.targetValue == -9999) // ensures that the search is based on index
            //    {
            //        DrawTextEx(
            //            font,
            //            TextFormat("Value found at index [%d] is '%d'", currentEvent.index, currentEvent.value),
            //            { startX + 0.0f,
            //            y + 165.0f },
            //            40,
            //            0,
            //            BLACK
            //        );
            //    }
            //    else if (currentEvent.index >= data.size() && eventQueue.empty())
            //    {
            //        DrawTextEx(
            //            font,
            //            TextFormat("Invalid Index Provided!"),
            //            { startX + 0.0f,
            //            y + 165.0f },
            //            40,
            //            0,
            //            RED
            //        );
            //    }
            //    else if (std::count(data.begin(), data.end(), currentEvent.targetValue) <= 0 && currentEvent.targetValue != -9999 && eventQueue.empty())
            //    {
            //        DrawTextEx(
            //            font,
            //            TextFormat("'%d' Not Found!", currentEvent.targetValue),
            //            { startX + 0.0f,
            //            y + 165.0f },
            //            40,
            //            0,
            //            RED
            //        );
            //    }
            //}

        }
    }

private:
    std::queue<Event> eventQueue;
    Event currentEvent{};
    float highlightTimer = 0.0f;

    Font font = Util::DefaultFont;
};
