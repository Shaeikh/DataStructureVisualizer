#pragma once

#include <iostream>
#include <vector>
#include <list>
#include "../../Events/EventBus.h"
#include <optional>

class LinkList {
public:
    LinkList(EventBus& bus) : eventBus(bus) {}

    void InsertAtHead(int value)
    {
        data.push_front(value);
        eventBus.emit({ EventType::Insert, 0, value });
    }

    void Insert(int value, std::optional<size_t> index = std::nullopt)
    {
        if (!index.has_value())
            return;

        if (index > data.size())
            return;

        auto it = data.begin();
        std::advance(it, index.value());

        data.insert(it, value);

        eventBus.emit({ EventType::Insert, index.value(), value });
    }

    void Erase(size_t index)
    {
        if (index >= data.size())
            return;

        auto it = data.begin();
        std::advance(it, index);

        int value = *it;

        data.erase(it);

        eventBus.emit({ EventType::Erase, index, value });
    }

    void Update(size_t index, int value)
    {
        if (index >= data.size())
            return;

        auto it = data.begin();
        std::advance(it, index);

        *it = value;

        eventBus.emit({ EventType::Update, index, value });
    }

    //std::optional<int> Search(bool byIndex, int indexOrValue)
    // there is no indexing, returning true if found 
    bool Search(int value)
    {
        //if (byIndex)
        //{
        //    size_t idx = static_cast<size_t>(indexOrValue);

        //    if (idx >= data.size())
        //        return std::nullopt;

        //    auto it = data.begin();
        //    std::advance(it, idx);

        //    eventBus.emit({ EventType::Search, idx, *it });

        //    return *it;
        //}
        //else
        {
            size_t i = 0;

            for (auto& val : data)
            {
                eventBus.emit({ EventType::Search, i, val, value });

                if (val == value)
                    return true;

                i++;
            }
        }

        return false;
    }

    //void Display()
    //{
    //    for (auto& v : data)
    //        std::cout << v << " ";

    //    std::cout << std::endl;
    //}

    const std::list<int>& GetData() const
    {
        return data;
    }

private:
    std::list<int> data;
    EventBus& eventBus;
};