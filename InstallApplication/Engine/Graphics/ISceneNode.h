#pragma once

#include <Engine/Graphics/3d/Camera.hpp>

class ISceneNode {

public:
	virtual void VRender(Camera* camera, double deltaTime) = 0;
	
};