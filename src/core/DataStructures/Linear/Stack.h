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
        if (data.size() == 20)
            return;
        data.push_front(value);

        eventBus.emit({ EventType::Push, 0, value });
    }

    void Pop()
    {
        if (data.empty())
            return;

        int tmp = data.front();
        data.pop_front();

        eventBus.emit({ EventType::Pop, 0, tmp });
    }

    void Update(int value)
    {
        if (data.empty())
            return;

        data.front() = value;

        eventBus.emit({ EventType::Update, 0, value });
    }

    int Top()
    {
        if (!data.empty())
            return data.front();
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