#pragma once
#include <vector>
#include <initializer_list>
#include "Button.h"

class Column
{
private:
    std::vector<Button*> children;
    float spacing = 10.0f;

public:
    Column(float space = 10.0f) : spacing(space) {}

    void Add(std::initializer_list<Button*> buttons)
    {
        for (Button* b : buttons)
            children.push_back(b);
    }

    void Layout(Vector2 startPosition)
    {
        float currentY = startPosition.y;
        
        float currentX = startPosition.x;

        float totalHeight = 0.0f;
        for (auto* child : children)
        {
            totalHeight += child->GetHeight() + spacing;
        }

        Rectangle container = { startPosition.x - 20.0f, startPosition.y, children[0]->GetWidth() + 40.0f, totalHeight };

        //DrawRectanglePro(container, {}, 0.0f, RED);

        for (auto* child : children)
        {
            currentX = (container.x + (container.width - child->GetWidth())/ 2 );
            child->SetPosition({ currentX, currentY });
            currentY += child->GetHeight() + spacing;
        }
    }

    void Update()
    {
        for (auto* child : children)
            child->Update();
    }

    void Render()
    {
        for (auto* child : children)
            child->Draw();
    }
};
