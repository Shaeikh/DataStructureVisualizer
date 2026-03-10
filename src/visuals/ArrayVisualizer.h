#include "raylib.h"
#include <vector>
#include <queue>

#include "../core/Events/EventBus.h"

#include "../util/util.h"

class ArrayVisualizer : public IObserver {
public:
    void OnEvent(const Event& e) override {

        if (e.type == EventType::Search) {
            // Search events gon animate step by step
            eventQueue.push(e);
        }
        else {
            // Insert/Erase/Update will animate immediately no delay
            while (!eventQueue.empty())
                eventQueue.pop();

            currentEvent = e;
            highlightTimer = 0.5f;
        }
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

    void Render(const std::vector<int>& data) {
        int cellWidth = 60;
        int cellHeight = 60;
        int startX = 40;
        int y = 300;
        
        for (size_t i = 0; i < data.size(); i++) 
        {
            Color color = WHITE;

            if (highlightTimer > 0) {
                if (currentEvent.type == EventType::Insert && i == currentEvent.index)
                    color = GREEN;

                if (currentEvent.type == EventType::Erase && i == currentEvent.index)
                    color = RED;

                if (currentEvent.type == EventType::Update && i == currentEvent.index)
                    color = YELLOW;

                if (currentEvent.type == EventType::Search && i == currentEvent.index)
                {
                    color = ORANGE;
                }
            }

            Rectangle rect = {
                startX + i * cellWidth, 
                y, 
                cellWidth + 4, 
                cellHeight
            };

            DrawRectanglePro(
                rect, {}, 0,
                color
            );

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
                { (startX + i * cellWidth + (cellWidth - textSize.x) / 2),
                y + (cellHeight - textSize.y) / 2 },
                fontSize,
                0,
                BLACK
            );

            DrawTextEx(
                font,
                TextFormat("%d", i),
                { startX + i * cellWidth + 22 - 0.0f,
                y + 70 - 0.0f },
                fontSize,
                0,
                GRAY
            );
            if (currentEvent.type == EventType::Search)
            {
                if (eventQueue.empty())
                    DrawText(
                        "Search Result",
                        startX + 25,
                        y + 120,
                        40,
                        GRAY
                    );

                if (currentEvent.targetValue == data[i] && eventQueue.empty())
                {
                    DrawText(
                        TextFormat("'%d' is at index [%d]", currentEvent.value, currentEvent.index),
                        startX + 25,
                        y + 155,
                        30,
                        BLACK
                    );
                }
                else if (currentEvent.index == i && eventQueue.empty() && currentEvent.targetValue == -9999) // ensures that the search is based on index
                {
                    DrawText(
                        TextFormat("Value found at index [%d] is '%d'", currentEvent.index, currentEvent.value),
                        startX + 25,
                        y + 155,
                        30,
                        BLACK
                    );
                }
                else if (currentEvent.index >= data.size() && eventQueue.empty())
                {
                    DrawText(
                        TextFormat("Invalid Index Provided!"),
                        startX + 25,
                        y + 155,
                        30,
                        RED
                    );
                }
                else if (std::count(data.begin(), data.end(), currentEvent.targetValue) <= 0 && currentEvent.targetValue != -9999 && eventQueue.empty())
                {
                    DrawText(
                        TextFormat("'%d' Not Found!", currentEvent.targetValue),
                        startX + 25,
                        y + 155,
                        30,
                        RED
                    );
                }
            }
            
        }
    }

private:
    std::queue<Event> eventQueue;
    Event currentEvent{};
    float highlightTimer = 0.0f;
    
    Font font = Util::DefaultFont;
};
