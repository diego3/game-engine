#pragma once

#include <Engine/Graphics/GlfwWindowSystem.h>

class UIManager
{
public:
	UIManager();

	void Initialize(GlfwWindowSystem* windowSystem);

	void Destroy();

	void Render(float deltaMilis);

	void SetActive(bool active);
private:
	bool my_tool_active;

	float colors[4];

	bool active;
};

