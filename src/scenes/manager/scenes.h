#include "SceneManager.h"

// Core
#include "../../core/DataStructures/Linear/Array.h"
#include "../../core/DataStructures/Linear/LinkList.h"
#include "../../core/DataStructures/Linear/Stack.h"
#include "../../core/DataStructures/Linear/Queue.h"

// Visualizers
#include "../../visuals/ArrayVisualizer.h"
#include "../../visuals/LinkListVisualizer.h"
#include "../../visuals/StackVisualizer.h"


// UI componenents
#include "../../ui/Button.h"
#include "../../ui/Row.h"
#include "../../ui/Alert.h"
#include "../../ui/TextInputField.h"
#include "../../ui/Container.h"

class ArrayScene
	: public Scene
{
private:
	EventBus bus;
	Array array = Array(bus);
	ArrayVisualizer visualizer;

	std::vector<std::string> historyStack;
	
	// Button/Row
	Vector2 bDimension     = { 200, 60 };
	Button b_insert = Button({ 0,0,bDimension.x,bDimension.y}, "Insert", 40);
	Button b_update = Button({ 0,0,bDimension.x,bDimension.y }, "Update", 40);
	Button b_delete = Button({ 0,0,bDimension.x,bDimension.y }, "Delete", 40);
	Button b_search= Button({ 0,0,bDimension.x,bDimension.y }, "Search", 40);
	Row r_options = Row(20);

	// Input Fields
	float inputFieldWidth = 240.0f;
	InputField inputIndex = InputField(inputFieldWidth, 60.0f, "Index", 3);
	InputField inputValue = InputField(inputFieldWidth, 60.0f, "Value", 3);

	// Alerts
	Alert alertArrayFull = Alert("Array Full", "Array is limited to 10 elements.");
	Alert alertArrayEmpty = Alert("Array Empty", "Array is empty.");
	Alert alertInvalidIndex = Alert("Invalid Index", "Please provide a valid index between ...");
	Alert alertSearchInputNotProvided = Alert("Empty Input", "Please provide a valid index or a value to perform the search.");


	// Containers
	Container containerDefinition = Container("Definition", Rectangle{20, 30, GetScreenWidth() - 40.0f, 180.0f});
	Container containerHistory = Container("History", Rectangle{ GetScreenWidth() - 480.0f, 260.0f, 460.0f, GetScreenHeight() - 280.0f }, 0.1);
	Container containerVisualization = Container("Visualization", Rectangle{ 20, 260.0f, GetScreenWidth() - 540.0f, GetScreenHeight() - 280.0f }, 0.05f);
	Container containerOperations = Container("Operations", Rectangle{ 40, GetScreenHeight() - 270.0f, GetScreenWidth() - 580.0f, GetScreenHeight() - 850.0f }, 0.1f);

	// Font (duh)
	Font font = Util::DefaultFont;
public:
	ArrayScene()
	{
		bus.subscribe(&visualizer);

		// Adding Buttons to the row (the inconsistency in naming is ridiculous oml)
		r_options.Add(&b_insert);
		r_options.Add(&b_update);
		r_options.Add(&b_delete);
		r_options.Add(&b_search);
	}
	void Render() override;
	void Update(float dt) override;
};

class LinkListScene
	: public Scene
{
public:
	LinkListScene()
	{
		bus.subscribe(&visualizer);

		// Adding Buttons to the row (the inconsistency in naming is ridiculous oml)
		r_options.Add(&b_insert);
		r_options.Add(&b_update);
		r_options.Add(&b_delete);
		r_options.Add(&b_search);
	}
	void Render() override;
	void Update(float dt) override;
private:
	EventBus bus;
	LinkList linkList = LinkList(bus);
	LinkListVisualizer visualizer;

	std::vector<std::string> historyStack;

	// Button/Row
	Vector2 bDimension = { 200, 60 };
	Button b_insert = Button({ 0,0,bDimension.x,bDimension.y }, "Insert", 40);
	Button b_update = Button({ 0,0,bDimension.x,bDimension.y }, "Update", 40);
	Button b_delete = Button({ 0,0,bDimension.x,bDimension.y }, "Delete", 40);
	Button b_search = Button({ 0,0,bDimension.x,bDimension.y }, "Search", 40);
	Row r_options = Row(20);

	// Input Fields
	float inputFieldWidth = 240.0f;
	InputField inputIndex = InputField(inputFieldWidth, 60.0f, "Index", 3);
	InputField inputValue = InputField(inputFieldWidth, 60.0f, "Value", 3);

	// Alerts
	Alert alertLLFull = Alert("Link List Full", "Linked List is constrained to hold 12 elements at most.");
	Alert alertLLEmpty = Alert("Link List Empty", "Linked List is empty.");
	Alert alertInvalidIndex = Alert("Invalid Index", "Please provide a valid index between ...");
	Alert alertSearchInputNotProvided = Alert("Empty Value Field", "Please provide a valid value to perform the search.");


	// Containers
	Container containerDefinition = Container("Definition", Rectangle{ 20, 30, GetScreenWidth() - 40.0f, 180.0f });
	Container containerHistory = Container("History", Rectangle{ GetScreenWidth() - 480.0f, 260.0f, 460.0f, GetScreenHeight() - 280.0f }, 0.1);
	Container containerVisualization = Container("Visualization", Rectangle{ 20, 260.0f, GetScreenWidth() - 540.0f, GetScreenHeight() - 280.0f }, 0.05f);
	Container containerOperations = Container("Operations", Rectangle{ 40, GetScreenHeight() - 270.0f, GetScreenWidth() - 580.0f, GetScreenHeight() - 850.0f }, 0.1f);

	// Font (duh)
	Font font = Util::DefaultFont;
};

class StackScene
	: public Scene
{
private:
	EventBus bus;
	Stack stack = Stack(bus);
	StackVisualizer visualizer;

	std::vector<std::string> historyStack;

	// Button/Row
	Vector2 bDimension = { 200, 60 };
	Button b_push = Button({ 0,0,bDimension.x,bDimension.y }, "Push", 40);
	Button b_update = Button({ 0,0,bDimension.x,bDimension.y }, "Update", 40);
	Button b_pop = Button({ 0,0,bDimension.x,bDimension.y }, "Pop", 40);
	//Button b_search = Button({ 0,0,bDimension.x,bDimension.y }, "Search", 40);
	Row r_options = Row(20);

	// Input Fields
	float inputFieldWidth = 240.0f;
	//InputField inputIndex = InputField(inputFieldWidth, 60.0f, "Index", 3);
	InputField inputValue = InputField(inputFieldWidth, 60.0f, "Value", 3);

	// Alerts
	Alert alertStackFull = Alert("Stack Full", "Stack is limited to 8 elements.");
	Alert alertStackEmpty = Alert("Stack Empty", "There are no elements inside the stack.");
	//Alert alertInvalidIndex = Alert("Invalid Index", "Please provide a valid index between ...");
	//Alert alertSearchInputNotProvided = Alert("Empty Input", "Please provide a value to perform the search.");


	// Containers
	Container containerDefinition = Container("Definition", Rectangle{ 20, 30, GetScreenWidth() - 40.0f, 180.0f });
	Container containerHistory = Container("History", Rectangle{ GetScreenWidth() - 480.0f, 260.0f, 460.0f, GetScreenHeight() - 280.0f }, 0.1);
	Container containerVisualization = Container("Visualization", Rectangle{ 20, 260.0f, GetScreenWidth() - 540.0f, GetScreenHeight() - 280.0f }, 0.05f);
	Container containerOperations = Container("Operations", Rectangle{ 40, GetScreenHeight() - 270.0f, GetScreenWidth() - 580.0f, GetScreenHeight() - 850.0f }, 0.1f);

	// Font (duh)
	Font font = Util::DefaultFont;
public:
	StackScene()
	{
		bus.subscribe(&visualizer);

		// Adding Buttons to the row (the inconsistency in naming is ridiculous oml)
		r_options.Add(&b_push);
		r_options.Add(&b_update);
		r_options.Add(&b_pop);
		//r_options.Add(&b_search);
	}
	void Render() override;
	void Update(float dt) override;
};

class QueueScene
	: public Scene
{
private:
	EventBus bus;
	Queue queue = Queue(bus);
	StackVisualizer visualizer;

	std::vector<std::string> historyStack;

	// Button/Row
	Vector2 bDimension = { 200, 60 };
	Button b_push = Button({ 0,0,bDimension.x,bDimension.y }, "Push", 40);
	Button b_update = Button({ 0,0,bDimension.x,bDimension.y }, "Update", 40);
	Button b_pop = Button({ 0,0,bDimension.x,bDimension.y }, "Pop", 40);
	//Button b_search = Button({ 0,0,bDimension.x,bDimension.y }, "Search", 40);
	Row r_options = Row(20);

	// Input Fields
	float inputFieldWidth = 240.0f;
	//InputField inputIndex = InputField(inputFieldWidth, 60.0f, "Index", 3);
	InputField inputValue = InputField(inputFieldWidth, 60.0f, "Value", 3);

	// Alerts
	Alert alertQueueFull = Alert("Stack Full", "Stack is limited to 8 elements.");
	Alert alertQueueEmpty = Alert("Stack Empty", "There are no elements inside the stack.");
	//Alert alertInvalidIndex = Alert("Invalid Index", "Please provide a valid index between ...");
	//Alert alertSearchInputNotProvided = Alert("Empty Input", "Please provide a value to perform the search.");


	// Containers
	Container containerDefinition = Container("Definition", Rectangle{ 20, 30, GetScreenWidth() - 40.0f, 180.0f });
	Container containerHistory = Container("History", Rectangle{ GetScreenWidth() - 480.0f, 260.0f, 460.0f, GetScreenHeight() - 280.0f }, 0.1);
	Container containerVisualization = Container("Visualization", Rectangle{ 20, 260.0f, GetScreenWidth() - 540.0f, GetScreenHeight() - 280.0f }, 0.05f);
	Container containerOperations = Container("Operations", Rectangle{ 40, GetScreenHeight() - 270.0f, GetScreenWidth() - 580.0f, GetScreenHeight() - 850.0f }, 0.1f);

	// Font (duh)
	Font font = Util::DefaultFont;
public:
	QueueScene()
	{
		bus.subscribe(&visualizer);

		// Adding Buttons to the row (the inconsistency in naming is ridiculous oml)
		r_options.Add(&b_push);
		r_options.Add(&b_update);
		r_options.Add(&b_pop);
		//r_options.Add(&b_search);
	}
	void Render() override;
	void Update(float dt) override;
};