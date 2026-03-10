#pragma once

#include <iostream>
#include <vector>
#include "../../Events/EventBus.h"

class Array {
public:
    Array(EventBus& bus) : eventBus(bus) {}

    void Insert(size_t index, int value)
    {
        if (data.size() == 20)
            return;
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

    std::optional<int> Search(bool byIndex, int indexOrValue)
    {
        if (byIndex)
        {
            size_t idx = static_cast<size_t>(indexOrValue);

            eventBus.emit({ EventType::Search, idx, idx < data.size() ? data[idx] : 0 });
            if (idx < data.size())
            {
                return data[idx];
            }
        }
        else
        {
            int idx = -1;
            for (size_t i = 0; i < data.size(); i++)
            {
                eventBus.emit({ EventType::Search, i, data[i], indexOrValue });
                if (data[i] == indexOrValue)
                {
                    idx = i;
                    break;
                }
            }

            if (idx != -1)
                return idx;
        }

        return std::nullopt;
    }

    const std::vector<int>& GetData() const {
        return data;
    }

private:
    std::vector<int> data;
    EventBus& eventBus;
};