#ifndef _GLOBAL__STATEMENT_H_
#define _GLOBAL__STATEMENT_H_

#include <glm/glm.hpp>

const static double pi = 3.1415926;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
bool firstMouse = true;
//float lastX = 800.0f / 2.0;
//float lastY = 800.0f / 2.0;
float fov = 45.0f;
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

float vertices[] = {
		-0.3f, -0.3f, -0.3f,  0.0f, 0.0f,
		 0.3f, -0.3f, -0.3f,  1.0f, 0.0f,
		 0.3f,  0.3f, -0.3f,  1.0f, 1.0f,
		 0.3f,  0.3f, -0.3f,  1.0f, 1.0f,
		-0.3f,  0.3f, -0.3f,  0.0f, 1.0f,
		-0.3f, -0.3f, -0.3f,  0.0f, 0.0f,

		-0.3f, -0.3f,  0.3f,  0.0f, 0.0f,
		 0.3f, -0.3f,  0.3f,  1.0f, 0.0f,
		 0.3f,  0.3f,  0.3f,  1.0f, 1.0f,
		 0.3f,  0.3f,  0.3f,  1.0f, 1.0f,
		-0.3f,  0.3f,  0.3f,  0.0f, 1.0f,
		-0.3f, -0.3f,  0.3f,  0.0f, 0.0f,

		-0.3f,  0.3f,  0.3f,  1.0f, 0.0f,
		-0.3f,  0.3f, -0.3f,  1.0f, 1.0f,
		-0.3f, -0.3f, -0.3f,  0.0f, 1.0f,
		-0.3f, -0.3f, -0.3f,  0.0f, 1.0f,
		-0.3f, -0.3f,  0.3f,  0.0f, 0.0f,
		-0.3f,  0.3f,  0.3f,  1.0f, 0.0f,

		 0.3f,  0.3f,  0.3f,  1.0f, 0.0f,
		 0.3f,  0.3f, -0.3f,  1.0f, 1.0f,
		 0.3f, -0.3f, -0.3f,  0.0f, 1.0f,
		 0.3f, -0.3f, -0.3f,  0.0f, 1.0f,
		 0.3f, -0.3f,  0.3f,  0.0f, 0.0f,
		 0.3f,  0.3f,  0.3f,  1.0f, 0.0f,

		-0.3f, -0.3f, -0.3f,  0.0f, 1.0f,
		 0.3f, -0.3f, -0.3f,  1.0f, 1.0f,
		 0.3f, -0.3f,  0.3f,  1.0f, 0.0f,
		 0.3f, -0.3f,  0.3f,  1.0f, 0.0f,
		-0.3f, -0.3f,  0.3f,  0.0f, 0.0f,
		-0.3f, -0.3f, -0.3f,  0.0f, 1.0f,

		-0.3f,  0.3f, -0.3f,  0.0f, 1.0f,
		 0.3f,  0.3f, -0.3f,  1.0f, 1.0f,
		 0.3f,  0.3f,  0.3f,  1.0f, 0.0f,
		 0.3f,  0.3f,  0.3f,  1.0f, 0.0f,
		-0.3f,  0.3f,  0.3f,  0.0f, 0.0f,
		-0.3f,  0.3f, -0.3f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
};

#endif