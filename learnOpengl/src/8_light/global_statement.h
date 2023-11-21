#ifndef _GLOBAL__STATEMENT_H_
#define _GLOBAL__STATEMENT_H_

#include <glm/glm.hpp>

const int screenwidth = 800; const int screenheight = 800;
double lastX = (double)screenwidth / 2.0;
double lastY = (double)screenheight / 2.0;
double sensitivity = 0.013;  float speed = 0.1;
glm::vec3 ws = glm::vec3(0.0, 0.0, -1.0f);
glm::vec3 ad = glm::vec3(-1.0f, 0.0, 0.0);
float yaw = -90.0f, dyaw = 0.0;
float pitch = 0.0f, dpitch = 0.0;
glm::vec3 camerapos = glm::vec3(0.0, 0.0, -4.0f);
const static double pi = 3.1415926;
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//bool firstMouse = true;
float fov = 45.0f;
// timing
float deltaTime = 0.0f;	
float lastFrame = 0.0f;

float vertices[] = {
		-0.3f, -0.3f, -0.3f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.3f, -0.3f, -0.3f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.3f,  0.3f, -0.3f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.3f,  0.3f, -0.3f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.3f,  0.3f, -0.3f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.3f, -0.3f, -0.3f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		-0.3f, -0.3f,  0.3f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.3f, -0.3f,  0.3f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.3f,  0.3f,  0.3f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.3f,  0.3f,  0.3f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.3f,  0.3f,  0.3f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.3f, -0.3f,  0.3f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		-0.3f,  0.3f,  0.3f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.3f,  0.3f, -0.3f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.3f, -0.3f, -0.3f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.3f, -0.3f, -0.3f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.3f, -0.3f,  0.3f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.3f,  0.3f,  0.3f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		 0.3f,  0.3f,  0.3f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.3f,  0.3f, -0.3f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		 0.3f, -0.3f, -0.3f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.3f, -0.3f, -0.3f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.3f, -0.3f,  0.3f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.3f,  0.3f,  0.3f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		-0.3f, -0.3f, -0.3f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.3f, -0.3f, -0.3f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		 0.3f, -0.3f,  0.3f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.3f, -0.3f,  0.3f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.3f, -0.3f,  0.3f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.3f, -0.3f, -0.3f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		-0.3f,  0.3f, -0.3f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.3f,  0.3f, -0.3f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		 0.3f,  0.3f,  0.3f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.3f,  0.3f,  0.3f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.3f,  0.3f,  0.3f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.3f,  0.3f, -0.3f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
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