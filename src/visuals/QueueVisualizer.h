#include "raylib.h"
#include <deque>
#include <queue>

#include "../core/Events/EventBus.h"

#include "../util/util.h"

class QueueVisualizer : public IObserver {
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

        //if (highlightTimer <= 0 && !eventQueue.empty()) {
        //    currentEvent = eventQueue.front();
        //    //std::cout << currentEvent.value << std::endl;
        //    eventQueue.pop();
        //    highlightTimer = 0.3f;
        //}
    }

    void Render(const std::deque<int>& data) {
        int cellWidth = 60;
        int cellHeight = 60;
        int startX = (20 + GetScreenWidth() - 540.0f) / 2 - (9 * cellWidth);
        int y = (260 + GetScreenHeight() - 280.0f) / 2 - cellHeight;
        //20, 260.0f, GetScreenWidth() - 540.0f, GetScreenHeight() - 280.0f

        // Stack container for containing all the elements
            //Container containerVisualization = Container("Visualization", Rectangle{ 20, 260.0f, GetScreenWidth() - 540.0f, GetScreenHeight() - 280.0f }, 0.05f);

        int containerWidth = 280;
        int containerHeight = 500;
        float containerX = 20 + (GetScreenWidth() - 540.0f - containerWidth) / 2;
        float containerY = 280;

        if (data.size() >= 1)
        {
            // Drawing "BACK"
            DrawTextEx(
                font,
                "Back",
                {
                    (float)(startX + (cellWidth) / 2) - MeasureTextEx(font, "Back", 30, 0).x / 2,
                    (float)y + (cellHeight)
                },
                30,
                0,
                DARKGRAY
            );

            // Drawing "Front"
            DrawTextEx(
                font,
                "Front",
                {
                    (float)(startX + data.size() * cellWidth) - MeasureTextEx(font, "Front", 30, 0).x,
                    (float)y - (cellHeight) / 2
                },
                30,
                0,
                DARKGRAY
            );

        }

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

            // Bezier Left
            DrawLineBezier(
                { 
                    40, 
                    300 
                }, 
                {
                    (float) startX - 25, 
                    (float)y + cellHeight / 2
                }, 
                5.0f, 
                BLACK
            );
            // Drawing arrow Left
            DrawTriangle(
                {
                    (float)startX,
                    (float)y + cellHeight / 2 
                },
                {
                    (float)startX - 25.0f,
                    (float)y + cellHeight / 2 - 15.0f
                },
                {
                    (float)startX - 25.0f,
                    (float)y + cellHeight / 2 + 15.0f 
                },
                BLACK
            );
            // Bezier Right
            DrawLineBezier(
                { 
                    (float)(data.size()) * cellWidth + startX, 
                    (float)y + cellHeight / 2 
                }, 
                { 
                    (float)(data.size()) * cellWidth + (startX * 2) - 40.0f - 25.0f, 
                    (float)y + cellHeight / 2 + 200 
                }, 
                5.0f, 
                BLACK
            );
            // Drawing arrow Right
            DrawTriangle(
                {
                    (float)(data.size()) * cellWidth + (startX * 2) - 40.0f, 
                    (float)y + cellHeight / 2 + 200
                },
                {
                    (float)(data.size())* cellWidth + (startX * 2) - 40.0f - 25.0f,
                    (float)y + cellHeight / 2 + 200 - 15.0f
                },
                {
                    (float)(data.size())* cellWidth + (startX * 2) - 40.0f - 25.0f,
                    (float)y + cellHeight / 2 + 200 + 15.0f
                },
                BLACK
            );

            //// Draw start-end spline circles with some details
            //DrawCircleV(startPoint, CheckCollisionPointCircle(mouse, startPoint, 10.0f) ? 14.0f : 8.0f, moveStartPoint ? RED : BLUE);
            //DrawCircleV(endPoint, CheckCollisionPointCircle(mouse, endPoint, 10.0f) ? 14.0f : 8.0f, moveEndPoint ? RED : BLUE);

            int fontSize = 30;
            const char* valueText = TextFormat("%d", data[i]);
            Vector2 textSize = MeasureTextEx(font, valueText, fontSize, 0);

            DrawTextEx(
                font,
                valueText,
                {
                    (startX + i * cellWidth + (cellWidth - textSize.x) / 2),
                    y + (cellHeight - textSize.y) / 2
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
