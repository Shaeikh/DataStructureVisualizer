#include "../../manager/Scenes.h"

void ArrayScene::Render()
{
	visualizer.Render(array.GetData());

	float bottomOffset = bDimension.y + 70.0f;
	r_options.Layout({ 60.0f, GetScreenHeight() - bottomOffset});
	r_options.Render();

	inputIndex.Layout({ 60.f, GetScreenHeight() - bottomOffset - bDimension.y - 20.0f });
	inputValue.Layout({ inputFieldWidth + 70.0f, GetScreenHeight() - bottomOffset - bDimension.y - 20.0f });

	inputIndex.Render();
	inputValue.Render();

	containerDefinition.Render();
	containerHistory.Render();
	containerVisualization.Render();
	containerOperations.Render();
}

void ArrayScene::Update(float dt)
{
	// Array Definition
	int fontSize = 50;
	std::string arrayDef = "A linear data structure that stores a collection of elements of the same data type in contiguous memory locations under a single variable name.";
	SetTextLineSpacing(-5);
	std::string arrayDefWrapped = Util::WrapTextToWidth(arrayDef, GetScreenWidth() - 20, fontSize);

	//Heading
	DrawTextEx(font, "Array:", { 40, 40 }, 60, 0, BLACK);

	//Definition
	DrawTextEx(font, arrayDefWrapped.c_str(), { 40, 100 }, fontSize, 0, DARKGRAY);

	DrawLineEx({ 0, 230.0f }, { GetScreenWidth() - 0.0f, 230.0f }, 4.0f, BLACK);

	DrawLineEx({ GetScreenWidth() - 500.0f, 230.0f}, {GetScreenWidth() - 500.0f, GetScreenHeight() - 0.0f }, 4.0f, BLACK);


	
	// Inputs and Buttons

	//int iis = inputIndex.GetText().size(); // Input Index Size
	//int ivs = inputValue.GetText().size(); // Input Value Size
	
	int ii = 
		inputIndex.GetText() != -9999 ?
			inputIndex.GetText() : GetRandomValue(0, array.GetData().size() == 0 ? 0 : array.GetData().size() - 1);

	int iv = 
		inputValue.GetText() != -9999 ?
			inputValue.GetText() : GetRandomValue(1, 99);

	b_insert.OnClick([&]() {
		if (array.GetData().size() == 20)
			alertArrayFull.Show();
		if (ii < 0 || ii > array.GetData().size())
		{
			alertInvalidIndex.SetSubText(TextFormat("Please provide a valid index ranging from 0-%d.", array.GetData().size()), 140.0f);
			alertInvalidIndex.Show();
		}
		array.Insert(ii, iv);
	});

	b_update.OnClick([&]() {
		if (array.GetData().size() == 0)
			alertArrayEmpty.Show();
		if (ii < 0 || ii >= array.GetData().size())
		{
			alertInvalidIndex.SetSubText(TextFormat("Please provide a valid index ranging from 0-%d.", array.GetData().size()  == 0 ? 0 : array.GetData().size() - 1), 140.0f);
			alertInvalidIndex.Show();
		}
		array.Update(ii, iv);
	});

	b_delete.OnClick([&]() {
		if (array.GetData().size() == 0)
			alertArrayEmpty.Show();
		if (ii < 0 || ii >= array.GetData().size())
		{
			alertInvalidIndex.SetSubText(TextFormat("Please provide a valid index ranging from 0-%d.", array.GetData().size() == 0 ? 0 : array.GetData().size() - 1), 140.0f);
			alertInvalidIndex.Show();
		}
		array.Erase(ii);
	});

	b_search.OnClick([&]() {
		//if (ii < 0 || ii > array.GetData().size())
		//{
		//	alertInvalidIndex.SetSubText(TextFormat("Please provide a valid index ranging from 0-%d.", array.GetData().size()), 140.0f);
		//	alertInvalidIndex.Show();
		//}
		if (array.GetData().size() == 0)
			alertArrayEmpty.Show();
		else if (inputIndex.GetText() == -9999 && inputValue.GetText() == -9999)
			alertSearchInputNotProvided.Show();
		else if (inputIndex.GetText() != -9999)
			array.Search(true, ii); // search by index
		else
			array.Search(false, iv); // search by value (index is priortized if both provided)
	});

	visualizer.Update(dt);
	r_options.Update();
	
	inputIndex.Update();
	inputValue.Update();

	alertArrayFull.Update(dt);
	alertArrayEmpty.Update(dt);
	alertInvalidIndex.Update(dt);
	alertSearchInputNotProvided.Update(dt);
	
}