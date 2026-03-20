#pragma once

#include <iostream>
#include <deque>
#include "../../Events/EventBus.h"

// ts ain't gon fly, better use deque (could use vec) instead of stack
class Stack {
public:
    Stack(EventBus& bus) : eventBus(bus) {}

    void Push(int value)
    {
        if (data.size() == 8)
            return;
        // using back instead of front cuz the visualizer going to show it down to top
        data.push_back(value);

        eventBus.emit({ EventType::Push, data.size() - 1, value});
    }

    void Pop()
    {
        if (data.empty())
            return;

        int tmp = data.back();
        
        
        data.pop_back();
        eventBus.emit({ EventType::Pop, data.size() - 1, tmp});

    }

    void Update(int value)
    {
        if (data.empty())
            return;

        data.back() = value;

        eventBus.emit({ EventType::Update, data.size() - 1, value});
    }

    int Top()
    {
        if (!data.empty())
            return data.back();
        return -9999;
    }

    //std::optional<int> Search(bool byIndex, int indexOrValue)
    //{
    //    if (byIndex)
    //    {
    //        size_t idx = static_cast<size_t>(indexOrValue);

    //        eventBus.emit({ EventType::Search, idx, idx < data.size() ? data[idx] : 0 });
    //        if (idx < data.size())
    //        {
    //            return data[idx];
    //        }
    //    }
    //    else
    //    {
    //        int idx = -1;
    //        for (size_t i = 0; i < data.size(); i++)
    //        {
    //            eventBus.emit({ EventType::Search, i, data[i], indexOrValue });
    //            if (data[i] == indexOrValue)
    //            {
    //                idx = i;
    //                break;
    //            }
    //        }

    //        if (idx != -1)
    //            return idx;
    //    }

    //    return std::nullopt;
    //}

    const std::deque<int>& GetData() const {
        return data;
    }

private:
    std::deque<int> data;
    EventBus& eventBus;
};