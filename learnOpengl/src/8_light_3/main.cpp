//所以相对路径的问题什么时候去解决。。。
#include <glad/glad.h>
#include <glfw/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <tool/stb_image.h>
#include <tool/shader.h>
#include <tool/camera.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <Windows.h>
 
#include "global_statement.h"

Camera camera(glm::vec3(0.0f, 0.0f, 4.0f));
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}
void when_resize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
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

	Shader shader("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/8_light_3/shader/vertex.glsl",
		"C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/8_light_3/shader/frag.glsl");
	unsigned int vbo, vao/*, ebo*/;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);  //glGenBuffers(1, &ebo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(5 * sizeof(float)));
	//glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	Shader lightshader("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/8_light_3/shader/light_vertex.glsl",
		"C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/8_light_3/shader/light_fragcolor.glsl");
	unsigned int lightvao, lightvbo;
	glGenVertexArrays(1, &lightvao);
	glGenBuffers(1, &lightvbo);
	glBindVertexArray(lightvao);
	glBindBuffer(GL_ARRAY_BUFFER, lightvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lightvertices), lightvertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	stbi_set_flip_vertically_on_load(true);

	//load texture-----------------------------------------------------------------------------------------------------------------------------
	int width, height, nrchannels;  unsigned int diffusemap, specularmap;
	glGenTextures(1, &diffusemap); glBindTexture(GL_TEXTURE_2D, diffusemap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data = stbi_load("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/static/pictures/container2.png",
		&width, &height, &nrchannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D); 
	}
	else { std::cout << "fail" << std::endl;  system("pause"); }
	glGenTextures(1, &specularmap); glBindTexture(GL_TEXTURE_2D, specularmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data2 = stbi_load("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/static/pictures/container2_specular.png",
		&width, &height, &nrchannels, 0);
	if (data2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else { std::cout << "fail" << std::endl;  system("pause"); }
	stbi_image_free(data);  stbi_image_free(data2);
	shader.use();
	shader.setInt("material.diffuse", 0);	 shader.setInt("material.specular", 1);
	//-----------------------------------------------------------------------------------------------------------------------------------------
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(w))
	{
		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(w);

		glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, diffusemap);
		glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, specularmap);
		//-----------------------------------------------------------------------------------------------------------------------------------------
		shader.use();
		float t = glfwGetTime(), temp = (t - pi / 2.0) * 1.0;
		glm::mat4 transform = glm::mat4(1.0f);
			/*glm::transpose(glm::mat4(
				0.5*cos(t)+0.7f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.5 * cos(t) + 0.7f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.5 * cos(t) + 0.7f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f)) 
			glm::transpose(glm::mat4(
				1.0f, 0.0f, 0.0f, 0.3 * cos(t),
				0.0f, 1.0f, 0.0f, 0.3 * sin(t),
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f)) *
			glm::transpose(glm::mat4(
				cos(temp),-sin(temp), 0.0f, 0.0f,
				sin(temp), cos(temp), 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f));*/
		shader.setMat4("trans1", transform);

        glm::mat4 view = glm::mat4(1.0f);
        view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, &view[0][0]);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective((float)glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
		shader.setMat4("projection", projection);
		//-----------------------------------------------------------------------------------------------------------------------------------------
		lightshader.use();
		glm::vec3 lightPos(0.0f, 0.0f, -5.0f);
		glm::mat4 lightmodel = glm::mat4(1.0f);
		lightmodel = glm::mat4(1.0f);
		//lightmodel = glm::rotate(lightmodel, t, glm::vec3(1.0f, 0.0, 0.0));
		lightmodel = glm::translate(lightmodel, lightPos);
		lightmodel = glm::scale(lightmodel, glm::vec3(0.1f));
		lightshader.setMat4("model", lightmodel);
		lightshader.setMat4("view", view);
		lightshader.setMat4("projection", projection);
		glBindVertexArray(lightvao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//-----------------------------------------------------------------------------------------------------------------------------------------
		shader.use();
		glm::vec3 lightColor(1.0, 1.0, 1.0);
		
		//lightColor.x = static_cast<float>(sin(glfwGetTime() * 2.0));
		//lightColor.y = static_cast<float>(sin(glfwGetTime() * 0.7));
		//lightColor.z = static_cast<float>(sin(glfwGetTime() * 1.3));
		glm::vec3 _lightPos = glm::vec3(lightmodel * glm::vec4(lightPos, 1.0));
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.4f); // decrease the influence
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.1f); // low influence
		shader.setVec3("light.position", _lightPos);
		shader.setVec3("light.ambient", ambientColor);
		shader.setVec3("light.diffuse", diffuseColor);
		shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        //shader.setVec3("material.ambient", white_rubber.Ambient );
        //shader.setVec3("material.diffuse", white_rubber.Diffuse);
        //shader.setVec3("material.specular", white_rubber.Specular);
		shader.setFloat("material.shininess", white_rubber.Shininess*128.0);

		shader.setVec3("viewpos", camera.Position);
		//-----------------------------------------------------------------------------------------------------------------------------------------
		glBindVertexArray(vao);

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * (float)i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.5f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		lightshader.use();
		glBindVertexArray(lightvao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//-----------------------------------------------------------------------------------------------------------------------------------------

		glfwSwapBuffers(w);
		glfwPollEvents();  
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &lightvao);
	glDeleteBuffers(1, &lightvbo);
	//glDeleteBuffers(1, &ebo);

	glfwTerminate();
	return 0;
}