#pragma once
#include <vector>
#include "Button.h"

class Column
{
private:
    std::vector<Button*> children;
    float spacing = 10.0f;

public:
    Column(float space = 10.0f) : spacing(space) {}

    void Add(Button* button)
    {
        children.push_back(button);
    }

    void Layout(Vector2 startPosition)
    {
        float currentY = startPosition.y;

        for (auto* child : children)
        {
            child->SetPosition({ startPosition.x, currentY });
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
