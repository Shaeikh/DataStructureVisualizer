#include "SceneManager.h"

class ArrayScene
	: public Scene
{
private:
	int arr[20];

public:
	void Render() override;
	void Update(double dt) override;
	
};