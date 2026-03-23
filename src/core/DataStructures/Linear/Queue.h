#pragma once

#include <iostream>
#include <deque>
#include "../../Events/EventBus.h"

class Queue
{
public:
	Queue(EventBus& bus)
		: eventBus(bus) {};
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

		int tmp = data.back();
		data.pop_back();
		eventBus.emit({ EventType::Pop, data.size() - 1, tmp });
	}

	void Update(int value)
	{
		if (data.empty())
			return;
		data.back() = value;
		eventBus.emit({ EventType::Update, data.size() - 1, value });
	}

	int Front() const
	{
		if (data.empty())
			return -9999;
		return data.back();
	}

	const std::deque<int>& GetData() const
	{
		return data;
	}

private:
	std::deque<int> data;
	EventBus& eventBus;
};