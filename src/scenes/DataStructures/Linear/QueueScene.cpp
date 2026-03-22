#include "../../manager/Scenes.h"

void QueueScene::Render()
{
	visualizer.Render(queue.GetData());

	float bottomOffset = bDimension.y + 70.0f;
	r_options.Layout({ 60.0f, GetScreenHeight() - bottomOffset });
	r_options.Render();

	//inputIndex.Layout({ 60.f, GetScreenHeight() - bottomOffset - bDimension.y - 20.0f });
	inputValue.Layout({ 60, GetScreenHeight() - bottomOffset - bDimension.y - 20.0f });

	//inputIndex.Render();
	inputValue.Render();

	containerDefinition.Render();
	containerHistory.Render();
	containerVisualization.Render();
	containerOperations.Render();

}

void QueueScene::Update(float dt)
{
	// Array Definition
	int fontSize = 50;
	std::string queueDef = "A linear data structure that follows First-In-First-Out (FIFO) order, allowing insertion from 'back' and deletion/pop from the 'front'.";
	SetTextLineSpacing(-5);
	std::string queueDefWrapped = Util::WrapTextToWidth(queueDef, GetScreenWidth() - 20, fontSize);

	//Heading
	DrawTextEx(font, "Queue:", { 40, 40 }, 60, 0, BLACK);

	//Definition
	DrawTextEx(font, queueDefWrapped.c_str(), { 40, 100 }, fontSize, 0, DARKGRAY);

	DrawLineEx({ 0, 230.0f }, { GetScreenWidth() - 0.0f, 230.0f }, 4.0f, BLACK);

	DrawLineEx({ GetScreenWidth() - 500.0f, 230.0f }, { GetScreenWidth() - 500.0f, GetScreenHeight() - 0.0f }, 4.0f, BLACK);

	// History stack
	Vector2 historyElementsPos = { GetScreenWidth() - 460.0f, 280.0f };
	//DrawRectangleRounded({ GetScreenWidth() - 480.0f, 260.0f, 460.0f, GetScreenHeight() - 280.0f }, 0.1, 255, BLACK);

	for (int i = 0; i < historyStack.size(); i++)
	{
		Color itemColor = BLACK;
		std::string str = historyStack[i];


		if (str[0] == 'P' && str[1] == 'u') // Push 
			itemColor = GREEN;
		else if (str[0] == 'P' && str[1] == 'o') // Pop
			itemColor = RED;
		else if (str[0] == 'U') // Update
			itemColor = PURPLE;

		DrawTextEx(
			font,
			historyStack[i].c_str(),
			{ historyElementsPos.x, historyElementsPos.y + i * 80 },
			40,
			0,
			itemColor
		);

		DrawTextEx(
			font,
			historyStack[i].substr(historyStack[i].find("\n\t\t")).c_str(),
			{ historyElementsPos.x, historyElementsPos.y + i * 80 },
			40,
			0,
			BLACK
		);
	}

	if (historyStack.size() == 10)
	{
		std::string lastElement = historyStack[9]; // total number of elements (to be displayed in history) are 9 as soon as it reaches 10, 10th element will be the only one displayed (at top)
		historyStack.clear();
		historyStack.push_back(lastElement);
	}

	// Inputs and Buttons

	//int iis = inputIndex.GetText().size(); // Input Index Size
	//int ivs = inputValue.GetText().size(); // Input Value Size

	//int ii =
	//	inputIndex.GetText() != -9999 ?
	//	inputIndex.GetText() : GetRandomValue(0, array.GetData().size() == 0 ? 0 : array.GetData().size() - 1);

	int iv =
		inputValue.GetText() != -9999 ?
		inputValue.GetText() : GetRandomValue(1, 99);

	b_push.OnClick([&]() {
		if (queue.GetData().size() == 8)
			alertQueueFull.Show();
		//else if (ii < 0 || ii > array.GetData().size())
		//{
		//	alertInvalidIndex.SetSubText(TextFormat("Please provide a valid index ranging from 0-%d.", array.GetData().size()), 140.0f);
		//	alertInvalidIndex.Show();
		//}
		else
		{
			queue.Push(iv);
			historyStack.push_back(TextFormat("Push:\n\t\tValue = %d", iv));
		}
		});

	b_update.OnClick([&]() {
		if (queue.GetData().size() == 0)
			alertQueueEmpty.Show();
		//else if (ii < 0 || ii >= array.GetData().size())
		//{
		//	alertInvalidIndex.SetSubText(TextFormat("Please provide a valid index ranging from 0-%d.", array.GetData().size() == 0 ? 0 : array.GetData().size() - 1), 140.0f);
		//	alertInvalidIndex.Show();
		//}
		else
		{
			queue.Update(iv);
			historyStack.push_back(TextFormat("Update:\n\t\tValue = %d", iv));
		}
		});

	b_pop.OnClick([&]() {
		if (queue.GetData().size() == 0)
			alertQueueEmpty.Show();
		//else if (ii < 0 || ii >= array.GetData().size())
		//{
		//	alertInvalidIndex.SetSubText(TextFormat("Please provide a valid index ranging from 0-%d.", array.GetData().size() == 0 ? 0 : array.GetData().size() - 1), 140.0f);
		//	alertInvalidIndex.Show();
		//}
		else
		{
			historyStack.push_back(TextFormat("Pop:\n\t\tValue: %d", queue.Front()));
			queue.Pop();
		}
		});

	//b_search.OnClick([&]() {
	//	//if (ii < 0 || ii > array.GetData().size())
	//	//{
	//	//	alertInvalidIndex.SetSubText(TextFormat("Please provide a valid index ranging from 0-%d.", array.GetData().size()), 140.0f);
	//	//	alertInvalidIndex.Show();
	//	//}
	//	if (array.GetData().size() == 0)
	//		alertArrayEmpty.Show();
	//	else if (inputIndex.GetText() == -9999 && inputValue.GetText() == -9999)
	//		alertSearchInputNotProvided.Show();
	//	else if (inputIndex.GetText() != -9999)
	//	{
	//		array.Search(true, ii); // search by index
	//		historyStack.push_back(TextFormat("Search:\n\t\tIndex = %d", ii));
	//	}
	//	else
	//	{
	//		array.Search(false, iv); // search by value (index is priortized if both provided)
	//		historyStack.push_back(TextFormat("Search:\n\t\tValue = %d", iv));
	//	}
	//	});

	visualizer.Update(dt);
	r_options.Update();

	//inputIndex.Update();
	inputValue.Update();

	alertQueueFull.Update(dt);
	alertQueueEmpty.Update(dt);
	//alertInvalidIndex.Update(dt);
	//alertSearchInputNotProvided.Update(dt);

}