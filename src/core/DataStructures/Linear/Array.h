#pragma once

#include <vector>
#include "../../Events/EventBus.h"

class Array {
public:
    Array(EventBus& bus) : eventBus(bus) {}

    void Insert(size_t index, int value)
    {
        if (index > data.size())
            return;

        data.insert(data.begin() + index, value);

        eventBus.emit({ EventType::Insert, index, value });
    }

    void Erase(size_t index)
    {
        if (index >= data.size())
            return;

        data.erase(data.begin() + index);

        eventBus.emit({ EventType::Erase, index, 0 });
    }

    void Update(size_t index, int value)
    {
        if (index >= data.size())
            return;

        data[index] = value;

        eventBus.emit({ EventType::Update, index, value });
    }

    const std::vector<int>& GetData() const {
        return data;
    }

private:
    std::vector<int> data;
    EventBus& eventBus;
};