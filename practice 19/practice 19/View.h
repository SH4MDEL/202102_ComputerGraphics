#pragma once
#include "stdafx.h"
struct View
{
	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;
	glm::vec3 cameraUp;
	glm::mat4 view;

	View();
};

