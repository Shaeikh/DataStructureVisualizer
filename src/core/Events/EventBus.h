#pragma once

#include <algorithm>
#include <vector>

#include "Observer.h"
#include "Event.h"

class EventBus
{
private:
	std::vector<IObserver*> observers_;

public:
	void subscribe(IObserver* observer)
	{
		observers_.push_back(observer);
	}

	void unsubscribe(IObserver* observer)
	{
		observers_.erase(
			std::remove(
				observers_.begin(), 
				observers_.end(), 
				observer
			),
			observers_.end()
		);
	}

	void emit(const Event& event)
	{
		for (auto* observer : observers_)
			observer->onEvent(event);
	}
};