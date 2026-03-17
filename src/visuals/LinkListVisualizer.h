#include "raylib.h"
#include <list>
#include <queue>

#include "../core/Events/EventBus.h"

#include "../util/util.h"

class LinkListVisualizer : public IObserver {
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

    void Render(const std::list<int>& data) {
        int valueCellWidth = 60; // refers to the wid of value holding field
        int linkCellWidth = 80; // referes to the wid of link to next node field
        int cellHeight = 60;

        int valueStartX = 40;
        int linkStartX = valueStartX + valueCellWidth;
        int _y = 450; // TODO: most shitiest tape together FIX!!!!!!!!!
        int y = 450;
        int gap = 60;
        int fontSize = 30;

        int compoundWidth = valueCellWidth + linkCellWidth + gap;

        int i = 0; // since std::list uses iterator rather than indices

        // Head node rectangle
        Rectangle headNodeRectangle = {
            40,
            y - 100,
            linkCellWidth,
            cellHeight
        };

        DrawRectanglePro(
            headNodeRectangle,
            { 0, 0 },
            0.0f,
            WHITE
        );

        DrawRectangleLinesEx(
            headNodeRectangle,
            4.0f,
            BLACK
        );

        DrawTextEx(
            font,
            "Head",
            {
                40.0f + (linkCellWidth - 
                    MeasureTextEx(
                        font, 
                        "Head", 
                        fontSize + 5.0f, 
                        0.0f
                    ).x
                ) / 2,
                (float) y - 100 - 40
            },
            fontSize + 5.0f,
            0.0f,
            DARKGRAY
        );

        auto firstNodeAddress = data.begin();
        std::string headAddress = data.size() > 0 ? TextFormat("%p", &(*firstNodeAddress)) : "NULL";
        if (headAddress != "NULL")
            headAddress = headAddress.substr(headAddress.size() - 5, 4);
        Vector2 textSize = MeasureTextEx(font, headAddress.c_str(), fontSize, 0);
        DrawTextEx(
            font,
            headAddress.c_str(),
            {
                40.0f + (linkCellWidth - textSize.x) / 2,
                y - 100 + (cellHeight - textSize.y) / 2
            },
            fontSize,
            0.0f,
            BLACK
        );
        
        for (auto it = data.begin(); it != data.end(); ++it)
        {
            Color color = WHITE;

            if (highlightTimer > 0) {
                if (currentEvent.type == EventType::Insert && i == currentEvent.index)
                    color = GREEN;

                if (currentEvent.type == EventType::Erase && i == currentEvent.index)
                    color = RED;

                if (currentEvent.type == EventType::Update && i == currentEvent.index)
                    color = PURPLE;

                if (currentEvent.type == EventType::Search && i == currentEvent.index)
                {
                    color = ORANGE;
                }
            }

            int x = valueStartX + i * compoundWidth;
            int y = _y;
            if (i >= 6)
            {
                x = valueStartX + (i - 6) * compoundWidth;
                y += 100;
            }
            // Value rectangle
            Rectangle valueRectangle = {
                x,
                y,
                valueCellWidth + 4,
                cellHeight
            };           

            DrawRectanglePro(
                valueRectangle, {}, 0,
                color
            );

            DrawRectangleLinesEx(
                valueRectangle,
                4.0f,
                BLACK
            );

            // Next node rectangle
            Rectangle linkRecangle = {
                x + valueCellWidth,
                y,
                linkCellWidth,
                cellHeight
            };

            DrawRectanglePro(
                linkRecangle,
                { 0, 0 },
                0.0f,
                BLACK
            );

            
            const char* valueText = TextFormat("%d", *it);
            Vector2 textSize = MeasureTextEx(font, valueText, fontSize, 0);

            // Rendering value text
            DrawTextEx(
                font,
                valueText,
                { 
                    x + (valueCellWidth - textSize.x) / 2,
                    y + (cellHeight - textSize.y) / 2 
                },
                fontSize,
                0,
                BLACK
            );
            
            // Rendering link addresses (each should have the next's address)
            auto nextIterator = std::next(it);
            std::string addressText;
            if (nextIterator == data.end())
                addressText = "NULL";
            else
            {
                addressText = TextFormat("%p", (void*)(&(*std::next(it, 1))));
                addressText = addressText.substr(addressText.size() - 5, 4);
            }
            DrawTextEx(
                font,
                addressText.c_str(),
                { 
                    x + valueCellWidth + 15.0f,
                    y + (cellHeight - textSize.y) / 2
                },
                fontSize,
                0,
                WHITE
            );

            // Rendering linking arrow
            float lineThickness = 8.0f;
            DrawLineEx(
                {
                    (float) x + valueCellWidth + linkCellWidth,
                    (float) y + (cellHeight) / 2 + lineThickness / 4
                },
                {
                    (float) x + valueCellWidth + linkCellWidth + 50,
                    (float) y + (cellHeight) / 2 + lineThickness / 4
                },
                lineThickness,
                BLACK
            );

            if (nextIterator != data.end())
            {
                DrawCircle(
                    (float)x + valueCellWidth + linkCellWidth + 50,
                    (float)y + (cellHeight) / 2 + lineThickness / 4,
                    10,
                    BLACK
                );
            }
            else
            {
                DrawLineEx(
                    {
                        (float)x + valueCellWidth + linkCellWidth + 50,
                        (float)y + (cellHeight) / 2 - 2
                    },
                    {
                        (float)x + valueCellWidth + linkCellWidth + 50,
                        (float)(y + (cellHeight) / 2 - 2) + 50
                    },
                    lineThickness,
                    BLACK
                );
                DrawRectangle(
                    x + valueCellWidth + linkCellWidth + 50 - 25,
                    y + (cellHeight) / 2 - 2 + 50,
                    50,
                    lineThickness,
                    BLACK
                );

                DrawRectangle(
                    x + valueCellWidth + linkCellWidth + 50 - 15,
                    y + (cellHeight) / 2 - 2 + 65,
                    30,
                    lineThickness,
                    BLACK
                );

                DrawRectangle(
                    x + valueCellWidth + linkCellWidth + 50 - 5,
                    y + (cellHeight) / 2 - 2 + 80,
                    10,
                    lineThickness,
                    BLACK
                );
            }

            if (currentEvent.type == EventType::Search)
            {
                if (eventQueue.empty())
                    DrawTextEx(
                        font,
                        "Search Result",
                        { (float) valueStartX,
                        _y + 160.0f },
                        50,
                        0,
                        DARKGRAY
                    );

                if (currentEvent.targetValue == *it && eventQueue.empty())
                {
                    DrawTextEx(
                        font,
                        TextFormat("Value [%d] found in the linked list", currentEvent.value),
                        { (float) valueStartX,
                        _y + 210.0f },
                        40,
                        0,
                        BLACK
                    );
                }
                //else if (currentEvent.index == i && eventQueue.empty() && currentEvent.targetValue == -9999) // ensures that the search is based on index
                //{
                //    DrawTextEx(
                //        font,
                //        TextFormat("Value found at index [%d] is '%d'", currentEvent.index, currentEvent.value),
                //        { (float) valueStartX,
                //        y + 165.0f },
                //        40,
                //        0,
                //        BLACK
                //    );
                //}
                //else if (currentEvent.index >= data.size() && eventQueue.empty())
                //{
                //    DrawTextEx(
                //        font,
                //        TextFormat("Invalid Index Provided!"),
                //        { (float) valueStartX,
                //        y + 165.0f },
                //        40,
                //        0,
                //        RED
                //    );
                //}
                else if (std::count(data.begin(), data.end(), currentEvent.targetValue) <= 0 && currentEvent.targetValue != -9999 && eventQueue.empty())
                {
                    DrawTextEx(
                        font,
                        TextFormat("Value [%d] Not Found!", currentEvent.targetValue),
                        { (float) valueStartX,
                        _y + 210.0f },
                        40,
                        0,
                        RED
                    );
                }
            }
            i++;
        }
    }

private:
    std::queue<Event> eventQueue;
    Event currentEvent{};
    float highlightTimer = 0.0f;

    Font font = Util::DefaultFont;
};