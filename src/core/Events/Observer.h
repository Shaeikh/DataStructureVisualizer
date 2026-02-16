#pragma once
#include "Event.h"

class IObserver {
public:
    virtual void onEvent(const Event& event) = 0;
    virtual ~IObserver() = default;
};
