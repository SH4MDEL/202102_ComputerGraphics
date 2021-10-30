#include "View.h"

View::View()
{
	cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
	cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
}