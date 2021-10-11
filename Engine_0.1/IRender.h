#pragma once

class Camera;

class IRender
{
public:
	virtual void render(Camera* camera) = 0;
};