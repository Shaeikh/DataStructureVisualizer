#pragma once

#include <algorithm>
#include <vector>
#include <optional>

#include "Observer.h"
#include "Event.h"

class EventBus
{
private:
	std::vector<IObserver*> observers;

public:
	void subscribe(IObserver* observer)
	{
		observers.push_back(observer);
	}

	void unsubscribe(IObserver* observer)
	{
		observers.erase(
			std::remove(
				observers.begin(), 
				observers.end(), 
				observer
			),
			observers.end()
		);
	}

	void emit(const Event& event)
	{
		for (auto* observer : observers)
			observer->OnEvent(event);
	}
};