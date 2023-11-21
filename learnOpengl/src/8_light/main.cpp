//所以相对路径的问题什么时候去解决。。。
#include <glad/glad.h>
#include <glfw/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <tool/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tool/shader.h>

#include <iostream>
#include <Windows.h>

#include "global_statement.h"

void when_resize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camerapos -= ws * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camerapos += ws * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camerapos += ad * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camerapos -= ad * speed;
	}
    float cameraSpeed = static_cast<float>(2.5 * deltaTime);//to do...
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    dyaw = sensitivity * (xpos - lastX);
    dpitch = sensitivity * (ypos - lastY);
    yaw += dyaw;    pitch += dpitch;
    ad = glm::vec3(cos(glm::radians(yaw + 90.0f)), 0.0, sin(glm::radians(yaw + 90.0f)) );
    if (pitch > 89.0) pitch = 89.0;
    if (pitch <-89.0) pitch =-89.0;
    ws = glm::vec3(cos(glm::radians(pitch))*cos(glm::radians(yaw)), -sin(glm::radians(pitch)), cos(glm::radians(pitch))*sin(glm::radians(yaw)) );
    lastX = xpos; lastY = ypos;
    //std::cout << xpos << " " << ypos << std::endl;
	//std::cout << yaw << " " << pitch << std::endl;
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    
}

int main() {
	glfwInit();
	GLFWwindow* w = glfwCreateWindow(800, 800, "w", NULL, NULL);
	glfwMakeContextCurrent(w);
	glfwSetFramebufferSizeCallback(w, when_resize);
	glfwSetCursorPosCallback(w, mouse_callback);
	//glfwSetScrollCallback(w, scroll_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1; 
	glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Shader shader("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/8_light/shader/vertex.glsl",
		"C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/8_light/shader/frag.glsl");

	unsigned int vbo, vao/*, ebo*/;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);  //glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	stbi_set_flip_vertically_on_load(true);

	int width, height, nrchannels;  unsigned int texture1, texture2;
	glGenTextures(1, &texture1); glBindTexture(GL_TEXTURE_2D, texture1);
	// 设置环绕和过滤方式
	//float borderColor[] = { 0.3f, 0.1f, 0.7f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data = stbi_load("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/static/pictures/container1.jpg",
		&width, &height, &nrchannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else { std::cout << "fail" << std::endl;  system("pause"); }
	glGenTextures(1, &texture2); glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data2 = stbi_load("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/static/pictures/awesomeface.png",
		&width, &height, &nrchannels, 0);
	if (data2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else { std::cout << "fail" << std::endl;  system("pause"); }
	stbi_image_free(data);  stbi_image_free(data2);

	shader.use();
	shader.setInt("texture1", 0);	 shader.setInt("texture2", 1);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(w))
	{
		glClearColor(0.30f, 0.15f, 0.65f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		processInput(w);
		//float currentFrame = static_cast<float>(glfwGetTime());
		//deltaTime = currentFrame - lastFrame;
		//lastFrame = currentFrame;

		glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, texture2);
		shader.use();
		float t = glfwGetTime(), temp = (t - pi / 2.0) * 1.0;
		glm::mat4 transform =
			/*glm::transpose(glm::mat4(
				0.5*cos(t)+0.7f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.5 * cos(t) + 0.7f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.5 * cos(t) + 0.7f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f)) */
			glm::transpose(glm::mat4(
				1.0f, 0.0f, 0.0f, 0.3 * cos(t),
				0.0f, 1.0f, 0.0f, 0.3 * sin(t),
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f)) *
			glm::transpose(glm::mat4(
				cos(temp),-sin(temp), 0.0f, 0.0f,
				sin(temp), cos(temp), 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "trans1"), 1, GL_FALSE, glm::value_ptr(transform));

		glm::vec3 lightcolor = glm::vec3(sin(t), 0.2, cos(t) );
		shader.setVec3("lightcolor", lightcolor);

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::rotate(view, glm::radians(yaw+90.0f), glm::vec3(0.0, 1.0, 0.0));
        view = glm::rotate(view, glm::radians(pitch), ad);
        view = glm::translate(view, camerapos);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, &view[0][0]);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective((float)glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
		shader.setMat4("projection", projection);

		glBindVertexArray(vao);

		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * (float)i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.5f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(w);
		glfwPollEvents(); 
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	//glDeleteBuffers(1, &ebo);

	glfwTerminate();
	return 0;
}