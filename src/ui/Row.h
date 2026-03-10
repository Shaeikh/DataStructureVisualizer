#pragma once
#include <vector>
#include "Button.h"

class Row
{
private:
    std::vector<Button*> children;
    float spacing = 10.0f;

public:
    Row(float space = 10.0f) : spacing(space) {}

    void Add(Button* button)
    {
        children.push_back(button);
    }

    void Layout(Vector2 startPosition)
    {
        float currentX = startPosition.x;

        for (auto* child : children)
        {
            child->SetPosition({ currentX, startPosition.y });
            currentX += child->GetWidth() + spacing;
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
