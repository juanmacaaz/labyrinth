#pragma once

#include "Camera.h"

class IRender
{
public:
	virtual void render(Camera* camera) = 0;
};