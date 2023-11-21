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

const static double pi = 3.1415926;

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
  glm::vec3(-1.7f,  3.0f, -5.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

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

	Shader shader("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/6_coordinate_system/shader/vertex.glsl",
		"C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/6_coordinate_system/shader/frag.glsl");

	/*float vertices[] = {
		//0.5*sin(t), 0.5*cos(t), 0.0f, 0.0f ,1.0f,
		 0.4f, 0.4f, 0.4f,  1.0f,  1.0f, 
		-0.4f, 0.4f, 0.4f,  0.0f,  1.0f, 
		 0.4f,-0.4f, 0.4f,	1.0f,  0.0f, 
		-0.4f,-0.4f, 0.4f,  0.0f,  0.0f, 
		 0.4f, 0.4f,-0.4f,  1.0f,  1.0f,
		-0.4f, 0.4f,-0.4f,  0.0f,  1.0f,
		 0.4f,-0.4f,-0.4f,	1.0f,  0.0f,
		-0.4f,-0.4f,-0.4f,  0.0f,  0.0f,
	};
	unsigned int index[] = {0,1,2 , 1,2,3 , 0,1,5 , 0,4,5 , 0,2,4 , 2,4,6 , 1,3,5 , 3,5,7 , 2,3,7 , 2,6,7 , 4,5,6 , 5,6,7};
	*/
	unsigned int vbo, vao/*, ebo*/;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);  //glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

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
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else { std::cout << "fail" << std::endl;  system("pause"); }
	glGenTextures(1, &texture2); glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data2 = stbi_load("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/static/pictures/a.png",
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
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	while (!glfwWindowShouldClose(w))
	{
		esc_quit(w);
		glClearColor(0.30f, 0.15f, 0.65f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, texture2);
		shader.use();

		float t = glfwGetTime(), temp = (t - pi / 2.0) * 1.0;
		// make sure to initialize matrix to identity matrix first
		//transform = glm::rotate(transform, temp, glm::vec3(0.0f, 0.0f, 1.0f));
		//transform = glm::translate(transform, glm::vec3(0.5f * cos(t) , 0.5f * sin(t), 1.0f ) );
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
				cos(temp), -sin(temp), 0.0f, 0.0f,
				sin(temp), cos(temp), 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f)) ;
		//view = glm::rotate(glm::mat4(1.0f), t, glm::vec3(1.0f, 0.0f, 0.0f));
		//view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f , -0.0f , -3.0f )) ;
		float r = 10.0f;
		float camx = sin(t) * r;	float camy = cos(t) * r;
		view = glm::lookAt(glm::vec3(camx, 0.0, camy), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 0.0));
		projection = glm::perspective((float)glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "trans1"), 1, GL_FALSE, glm::value_ptr(transform));
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, &view[0][0]);
		shader.setMat4("projection", projection);
		glBindVertexArray(vao);
		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * (float)i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(0.7f, 0.3f, 0.5f));
			glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glBindVertexArray(vao);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(w);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	//glDeleteBuffers(1, &ebo);

	glfwTerminate();
	return 0;
}
