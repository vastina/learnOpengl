//哦对了，相对路径的问题还是没解决，还是得打绝对路径，有点蠢了
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

const static double pi = 3.1415926;

void when_resize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void esc_quit(GLFWwindow* window) {
	if (glfwGetKey(window, 256/*escape*/) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() {
	glfwInit();
	GLFWwindow* w = glfwCreateWindow(800, 800, "w", NULL, NULL);
	glfwMakeContextCurrent(w);
	glfwSetFramebufferSizeCallback(w, when_resize);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;
	//glViewport(0, 0, 1000, 700);  glEnable(GL_PROGRAM_POINT_SIZE);

	Shader shader("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/5_transformation/shader/texture1.glsl",
		"C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/5_transformation/shader/texture2.glsl");

	float vertices[] = {
		//0.5*sin(t), 0.5*cos(t), 0.0f, 0.0f ,1.0f,
		 0.4f, 0.4f, 1.0f,  1.0f,  1.0f,
		-0.4f, 0.4f, 1.0f,  0.0f,  1.0f,
		 0.4f,-0.4f, 1.0f,	1.0f,  0.0f,
		-0.4f,-0.4f, 1.0f,  0.0f,  0.0f
	};
	unsigned int index[] = { 0,1,2 , 1,2,3 };

	unsigned int vbo, vao, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);  glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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
	unsigned char* data = stbi_load("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/static/pictures/3.jpg",
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

	while (!glfwWindowShouldClose(w))
	{
		esc_quit(w);
		glClearColor(0.25f, 0.15f, 0.55f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glm::mat4 transform = glm::mat4(1.0f);
		float t = glfwGetTime(), temp = (t - pi*0.0 / 2.0)*1.0;
		// make sure to initialize matrix to identity matrix first
		
		transform = glm::rotate(transform, temp, glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::translate(transform, glm::vec3(0.5f  , 0.5f , 0.0f ) );
	/*	glm::mat4 transform =
			glm::transpose(glm::mat4(
				0.5*cos(t)+0.7f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.5 * cos(t) + 0.7f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f)) 
			glm::transpose( glm::mat4(
				1.0f, 0.0f, 0.0f, 0.3 * cos(t),
				0.0f, 1.0f, 0.0f, 0.3 * sin(t),
				0.0f, 0.0f, 0.5f, 0.3 * cos(t),
				0.0f, 0.0f, 0.0f, 1.0f)) *
			glm::transpose( glm::mat4(
				cos(temp), -sin(temp), 0.0f, 0.0f,
				sin(temp),  cos(temp), 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f)) 
			 ;*/
		
		glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, texture2);

		shader.use();
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "trans1"), 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(w);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	glfwTerminate();
	return 0;
}
