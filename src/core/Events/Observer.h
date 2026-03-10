#pragma once
#include "Event.h"

class IObserver {
public:
    virtual void OnEvent(const Event& event) = 0;
    virtual ~IObserver() = default;
};
