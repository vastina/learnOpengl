#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <tool/shader.h>

#include <iostream>
#include <Windows.h>

#define STB_IMAGE_IMPLEMENTATION
#include <tool/stb_image.h>

const static double sqrt2 = 1.414213; //1.414213562373
const static double pi = 3.1415926;

void when_resize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height );
}

void esc_quit(GLFWwindow* window) {
	if (glfwGetKey(window, 256/*escape*/) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() {
	glfwInit();  
	GLFWwindow* w = glfwCreateWindow(800, 600, "w", NULL, NULL);
	glfwMakeContextCurrent(w);
	glfwSetFramebufferSizeCallback(w, when_resize);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;
	//glViewport(0, 0, 1000, 700);  glEnable(GL_PROGRAM_POINT_SIZE);

	Shader shader("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/4_texture_1/resource/texture2.txt", 
				  "C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/4_texture_1/resource/texture1.txt");

	float vertices[] = {
		//0.5*sin(time), 0.5*cos(time),
		 0.5f, 0.5f, 0.0f, 0.0f, 0.0f ,1.0f, 1.0f,  1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f ,0.0f,  0.0f,  1.0f,
		 0.5f,-0.5f, 0.0f, 1.0f, 0.0f ,0.0f,	 1.0f,  0.0f,
		-0.5f,-0.5f, 0.0f, 0.6f, 0.6f ,0.6f,  0.0f,  0.0f
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
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);   glBindVertexArray(0);

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrchannels;  unsigned int texture, texture2;
	glGenTextures(1, &texture); glBindTexture(GL_TEXTURE_2D, texture);
	// 设置环绕和过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	unsigned char* data = stbi_load("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/4_texture_1/resource/container.jpg",	
		&width, &height, &nrchannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}   else {  std::cout << "fail" << std::endl;  system("pause"); }

	//两个同时设置会有问题，必须分开，以及不是一data两用的问题。。。
	glGenTextures(1, &texture2); glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	/*stbi_image_free(data); 
	data = stbi_load("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/4_texture_1/resource/awesomeface.png",
		&width, &height, &nrchannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else { std::cout << "fail" << std::endl;  system("pause"); }*/
	//很奇怪的问题，相对路径会读取不出来
	unsigned char* data2 = stbi_load("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/4_texture_1/resource/awesomeface.png",
		&width, &height, &nrchannels, 0);
	if (data2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}   else { std::cout << "fail" << std::endl;  system("pause"); }
	stbi_image_free(data);  stbi_image_free(data2);

	shader.use();
	shader.setInt("texture1", 0);	shader.setInt("texture2", 1);

	while (!glfwWindowShouldClose(w))
	{
		esc_quit(w);
		glClearColor(0.35f, 0.05f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		double time = glfwGetTime();
		float temp = sin(time * 4);
		float vertices[] = {
			//0.5*sin(time), 0.5*cos(time),
			 0.5 * sin(time + pi * 1.0 / 4.0), 0.5 * cos(time + pi * 1.0 / 4.0), 0.0f, 0.2f, 0.4f ,0.8f, 1.0f,  1.0f,
			 0.5 * sin(time + pi * 3.0 / 4.0), 0.5 * cos(time + pi * 3.0 / 4.0), 0.0f, temp, 0.4f ,0.6f,  0.0f,  1.0f,
			 0.5 * sin(time + pi * 7.0 / 4.0), 0.5 * cos(time + pi * 7.0 / 4.0), 0.0f, 0.6f, temp ,0.4f,	 1.0f,  0.0f,
			 0.5 * sin(time + pi * 5.0 / 4.0), 0.5 * cos(time + pi * 5.0 / 4.0), 0.0f, 0.6f, 0.4f ,temp,  0.0f,  0.0f
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture);  
		glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, texture2);

		shader.use();
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