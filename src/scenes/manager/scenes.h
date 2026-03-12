#include "SceneManager.h"
#include "../../core/DataStructures/Linear/Array.h"
#include "../../visuals/ArrayVisualizer.h"
#include "../../ui/Button.h"
#include "../../ui/Row.h"
#include "../../ui/Alert.h"
#include "../../ui/TextInputField.h"
#include "../../ui/Container.h"


class ArrayScene
	: public Scene
{
private:
	EventBus        bus;
	Array array     = Array(bus);
	ArrayVisualizer visualizer;

	std::vector<std::string> historyStack;
	
	// UI Elements
	Vector2 bDimension     = { 200, 60 };
	Button b_insert = Button({ 0,0,bDimension.x,bDimension.y}, "Insert", 40);
	Button b_update = Button({ 0,0,bDimension.x,bDimension.y }, "Update", 40);
	Button b_delete = Button({ 0,0,bDimension.x,bDimension.y }, "Delete", 40);
	Button b_search= Button({ 0,0,bDimension.x,bDimension.y }, "Search", 40);
	Row r_options = Row(20);

	float inputFieldWidth = 240.0f;
	InputField inputIndex = InputField(inputFieldWidth, 60.0f, "Index", 3);
	InputField inputValue = InputField(inputFieldWidth, 60.0f, "Value", 3);

	Alert alertArrayFull = Alert("Array Full", "Array is limited to 10 elements.");
	Alert alertArrayEmpty = Alert("Array Empty", "Array is empty.");
	Alert alertInvalidIndex = Alert("Invalid Index", "Please provide a valid index between ...");
	Alert alertSearchInputNotProvided = Alert("Empty Input", "Please provide a valid index or a value to perform the search.");

	Font font = Util::DefaultFont;

	Container containerDefinition = Container("Definition", Rectangle{20, 30, GetScreenWidth() - 40.0f, 180.0f});
	Container containerHistory = Container("History", Rectangle{ GetScreenWidth() - 480.0f, 260.0f, 460.0f, GetScreenHeight() - 280.0f }, 0.1);
	Container containerVisualization = Container("Visualization", Rectangle{ 20, 260.0f, GetScreenWidth() - 540.0f, GetScreenHeight() - 280.0f }, 0.05f);
	Container containerOperations = Container("Operations", Rectangle{ 40, GetScreenHeight() - 270.0f, GetScreenWidth() - 580.0f, GetScreenHeight() - 850.0f }, 0.1f);

public:
	ArrayScene()
	{
		
		bus.subscribe(&visualizer);

		r_options.Add(&b_insert);
		r_options.Add(&b_update);
		r_options.Add(&b_delete);
		r_options.Add(&b_search);

		

		//historyStack.push_back("Lasat command");
		//historyStack.push_back("Lasat command2");
		//historyStack.push_back("Lasat command3");
		//historyStack.push_back("Lasat command4");
		//historyStack.push_back("Lasat command5");
		//historyStack.push_back("Lasat command6");
		//historyStack.push_back("Lasat command7");
	}
	void Render() override;
	void Update(float dt) override;
	
};