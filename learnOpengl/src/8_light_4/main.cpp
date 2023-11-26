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
#include <format>
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
unsigned int loadTexture(char const* path);

int main() {
	glfwInit();
	GLFWwindow* w = glfwCreateWindow(800, 800, "w", NULL, NULL);
	glfwMakeContextCurrent(w);
	glfwSetFramebufferSizeCallback(w, when_resize);
	glfwSetCursorPosCallback(w, mouse_callback);
	glfwSetScrollCallback(w, scroll_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1; 
	glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Shader shader("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/8_light_4/shader/vertex.glsl",
		"C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/8_light_4/shader/frag.glsl");
	unsigned int vbo, vao;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);  //glGenBuffers(1, &ebo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	Shader lightshader("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/8_light_4/shader/light_vertex.glsl",
		"C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/8_light_4/shader/light_fragcolor.glsl");
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
	unsigned int diffusemap = loadTexture("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/static/pictures/container2.png");
	unsigned int specularmap = loadTexture("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/static/pictures/container2_specular.png");
	unsigned int emissionmap = loadTexture("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/static/pictures/awesomeface.png");
 
	shader.use();
	shader.setInt("material.diffuse", 0);	 shader.setInt("material.specular", 1);		shader.setInt("material.emission", 2);
	//-----------------------------------------------------------------------------------------------------------------------------------------
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(w))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(w);

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//-----------------------------------------------------------------------------------------------------------------------------------------
		shader.use();
		float t = glfwGetTime(), temp = (t - pi / 2.0) * 2.5;
		glm::mat4 transform = glm::mat4(1.0f);
			/*glm::transpose(glm::mat4(
				0.5*cos(t * 2.0)+0.7f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.5 * cos(t * 2.0) + 0.7f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.5 * cos(t * 2.0) + 0.7f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f)) *
			glm::transpose(glm::mat4(
				1.0f, 0.0f, 0.0f, 1.5 * cos(t),
				0.0f, 1.0f, 0.0f, 2.5 * sin(t),
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f)) *
			glm::transpose(glm::mat4(
				cos(temp),-sin(temp), 0.0f, 0.0f,
				sin(temp), cos(temp), 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f));*/
		shader.setMat4("trans1", transform);

        glm::mat4 view = camera.GetViewMatrix();
		shader.setMat4("view", view);

        glm::mat4 projection = glm::perspective((float)glm::radians(camera.Zoom), 1.0f, 0.1f, 100.0f);
		shader.setMat4("projection", projection);
	//-----------------------------------------------------------------------------------------------------------------------------------------
		glm::vec3 _lightpos[4];
		lightshader.use();
		lightshader.setMat4("view", view);
		lightshader.setMat4("projection", projection);

		glBindVertexArray(lightvao);
		for (unsigned int i = 0; i < 4; i++) {
			glm::mat4 lightmodel = glm::mat4(1.0f);
			lightmodel = glm::translate(lightmodel, pointLightPositions[i]);
			lightmodel = glm::scale(lightmodel, glm::vec3(0.1f));
			lightshader.setMat4("model", lightmodel);
			_lightpos[i] = glm::vec3(lightmodel * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f) );
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		/*lightmodel = glm::translate(lightmodel, lightPos);
		translate是在变换后的坐标里面translate， 也就是说scale之后只会移动原来的0.1*lightpos
		而scale不改变为齐次操作额外添加的一个维度，所以先translate再scale， 或者这样：
		lightmodel = glm::scale(lightmodel, glm::vec3(0.1f)); lightmodel[3] += lightPos;*/
	//-----------------------------------------------------------------------------------------------------------------------------------------
		shader.use();
		glm::vec3 lightColor(1.0, 1.0, 1.0);	
		//lightColor.x = static_cast<float>(sin(glfwGetTime() * 2.0));
		//lightColor.y = static_cast<float>(sin(glfwGetTime() * 0.7));
		//lightColor.z = static_cast<float>(sin(glfwGetTime() * 1.3));
		//glm::vec3 _lightPos = glm::vec3(lightmodel * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.4f); 
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.1f); 
		for (unsigned int i = 0; i < 4; i++) {
			shader.setVec3(std::format("light[{}].position", i), _lightpos[i]);
			shader.setVec3(std::format("light[{}].ambient", i), ambientColor );
			shader.setVec3(std::format("light[{}].diffuse", i), diffuseColor );
			shader.setVec3(std::format("light[{}].specular", i), lightColor );
		}

		shader.setFloat("lightstrength.constant", 1.0);
		shader.setFloat("lightstrength.linear", 0.09f);
		shader.setFloat("lightstrength.quadratic", 0.032f);

		shader.setVec3("sunlight.direction", -0.2f, -1.0f, -0.3f);
		shader.setVec3("sunlight.ambient", ambientColor );
		shader.setVec3("sunlight.diffuse", diffuseColor );
		shader.setVec3("sunlight.specular", lightColor );

		shader.setVec3("flashlight.direction", camera.Front );
		shader.setVec3("flashlight.position", camera.Position );
		shader.setFloat("flashlight.cutoff", glm::cos(glm::radians(12.5f) ) );
		shader.setFloat("flashlight.outer_cutoff", glm::cos(glm::radians(17.5f) ) );
		shader.setVec3("flashlight.ambient", 0.1f, 0.1f, 0.1f);
		shader.setVec3("flashlight.diffuse", 0.8f, 0.8f, 0.8f);
		shader.setVec3("flashlight.specular", lightColor);

		shader.setVec3("viewpos", camera.Position);
		shader.setFloat("material.shininess", 32.0);
        shader.setFloat("move", t);
		shader.setFloat("t", t);
		
	//-----------------------------------------------------------------------------------------------------------------------------------------
		glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, diffusemap);
		glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, specularmap);
		glActiveTexture(GL_TEXTURE2); glBindTexture(GL_TEXTURE_2D, emissionmap);

		glBindVertexArray(vao);

		glm::mat4 model = glm::mat4(1.0f);
		shader.setMat4("model", model);

		for (unsigned int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * (float)i ;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.5f, 0.0f));
			shader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

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

unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}