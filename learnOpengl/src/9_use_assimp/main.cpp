#include <glad/glad.h>
#include <glfw/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <tool/shader.h>
#include <tool/camera.h>
#include <tool/model.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <format>
//#include <Windows.h>
 
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

int __stdcall main() {
	glfwInit();
	GLFWwindow* w = glfwCreateWindow(800, 800, "w", NULL, NULL);
	glfwMakeContextCurrent(w);
	glfwSetFramebufferSizeCallback(w, when_resize);
	glfwSetCursorPosCallback(w, mouse_callback);
	glfwSetScrollCallback(w, scroll_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1; 
	glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Shader shader("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/9_use_assimp/shader/vertex.glsl",
		"C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/9_use_assimp/shader/frag.glsl");
	unsigned int vbo, vao;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);  
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

	Shader lightshader("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/9_use_assimp/shader/light_vertex.glsl",
		"C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/9_use_assimp/shader/light_fragcolor.glsl");
	unsigned int lightvao, lightvbo;
	glGenVertexArrays(1, &lightvao);
	glGenBuffers(1, &lightvbo);
	glBindVertexArray(lightvao);
	glBindBuffer(GL_ARRAY_BUFFER, lightvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lightvertices), lightvertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//load texture-----------------------------------------------------------------------------------------------------------------------------
	unsigned int diffusemap = loadTexture("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/static/pictures/container2.png");
	unsigned int specularmap = loadTexture("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/static/pictures/container2_specular.png");
	unsigned int emissionmap = loadTexture("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/static/pictures/awesomeface.png");
	shader.use();
	shader.setInt("material.diffuse", 0);	
	shader.setInt("material.specular", 1);  
	shader.setInt("material.emission", 2);
 
	Shader modelshader("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/9_use_assimp/shader/nanosuitvertex.glsl",
		"C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/9_use_assimp/shader/nanosuitfrag.glsl");
	Model nanosuit("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/static/model/nanosuit/nanosuit.obj");
	std::vector<int> vt{};
	modelshader.use();
	for (auto tex : nanosuit.textures_loaded) {
		vt.push_back(tex.id);
		modelshader.setInt(tex.type, vt.size()-1);
	}

	Shader rockshader("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/9_use_assimp/shader/rock_vertex.glsl",
		"C:/Users/vastina/Desktop/learnOpengl/learnOpengl/src/9_use_assimp/shader/rock_frag.glsl");
	Model rock("C:/Users/vastina/Desktop/learnOpengl/learnOpengl/static/model/rock/rock.obj");
	std::vector<unsigned int> rock_vt{};
	rockshader.use();
	for (auto tex : rock.textures_loaded) {
		rock_vt.push_back(tex.id);
		rockshader.setInt(tex.type, rock_vt.size()-1);
	}

	//-----------------------------------------------------------------------------------------------------------------------------------------
	glEnable(GL_DEPTH_TEST);
	stbi_set_flip_vertically_on_load(true);
	glDepthFunc(GL_LESS);
	while (!glfwWindowShouldClose(w))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(w);

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
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
				0.0f, 0.0f, 0.0f, 1.0f)) 
			glm::transpose(glm::mat4(
				cos(temp),-sin(temp), 0.0f, 0.0f,
				sin(temp), cos(temp), 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f));*/
		shader.setMat4("trans1", transform);

        glm::mat4 view = camera.GetViewMatrix();
		shader.setMat4("view", view);

        glm::mat4 projection = glm::perspective((float)glm::radians(camera.Zoom), 1.0f, 0.1f, 50.0f);
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
			lightshader.setVec3("_light_fragcolor", point_color[i]);
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
		for (unsigned int i = 0; i < 4; i++) {
			shader.setVec3(std::format("light[{}].position", i), _lightpos[i]);
			shader.setVec3(std::format("light[{}].ambient", i), point_color[i] * glm::vec3(0.1) );
			shader.setVec3(std::format("light[{}].diffuse", i), point_color[i] * glm::vec3(0.4) );
			shader.setVec3(std::format("light[{}].specular", i), point_color[i] );
		}

		shader.setFloat("lightstrength.constant", 1.0);
		shader.setFloat("lightstrength.linear", 0.09f);
		shader.setFloat("lightstrength.quadratic", 0.032f);

		shader.setVec3("sunlight.direction", -0.2f, -1.0f, -0.3f);
		shader.setVec3("sunlight.ambient", sunambient );
		shader.setVec3("sunlight.diffuse", sundiffuse );
		shader.setVec3("sunlight.specular", sunspecular );

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

		modelshader.use();
		for (int i = 0; i < vt.size(); i++) {
			glActiveTexture(GL_TEXTURE+i);
			glBindTexture(GL_TEXTURE_2D, vt[i]);
		}
		for (unsigned int i = 0; i < 4; i++) {
			modelshader.setVec3(std::format("light[{}].position", i), _lightpos[i]);
			modelshader.setVec3(std::format("light[{}].ambient", i), point_color[i] * glm::vec3(0.1));
			modelshader.setVec3(std::format("light[{}].diffuse", i), point_color[i] * glm::vec3(0.4));
			modelshader.setVec3(std::format("light[{}].specular", i), point_color[i]);
		}
		modelshader.setFloat("material.shininess", 128.0);
		modelshader.setFloat("lightstrength.constant", 1.0);
		modelshader.setFloat("lightstrength.linear", 0.09f);
		modelshader.setFloat("lightstrength.quadratic", 0.032f);

		modelshader.setVec3("sunlight.direction", -0.2f, -1.0f, -0.3f);
		modelshader.setVec3("sunlight.ambient", sunambient);
		modelshader.setVec3("sunlight.diffuse", sundiffuse);
		modelshader.setVec3("sunlight.specular", sunspecular);

		modelshader.setVec3("flashlight.direction", camera.Front);
		modelshader.setVec3("flashlight.position", camera.Position);
		modelshader.setFloat("flashlight.cutoff", glm::cos(glm::radians(12.5f)));
		modelshader.setFloat("flashlight.outer_cutoff", glm::cos(glm::radians(17.5f)));
		modelshader.setVec3("flashlight.ambient", 0.1f, 0.1f, 0.1f);
		modelshader.setVec3("flashlight.diffuse", 0.8f, 0.8f, 0.8f);
		modelshader.setVec3("flashlight.specular", lightColor);

		modelshader.setVec3("viewpos", camera.Position);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0, 0.0, 4.0));
		model = glm::scale(model, glm::vec3(0.2));
		modelshader.setMat4("model", model);
		modelshader.setMat4("view", view);
		modelshader.setMat4("projection", projection);

		nanosuit.Draw(modelshader);
	//-----------------------------------------------------------------------------------------------------------------------------------------
		rockshader.use();
		for (unsigned int i = 0; i < rock_vt.size(); i++) {
			glActiveTexture(GL_TEXTURE + i);
			glBindTexture(GL_TEXTURE_2D, rock_vt[i]);
		}
		for (unsigned int i = 0; i < 4; i++) {
			rockshader.setVec3(std::format("light[{}].position", i), _lightpos[i]);
			rockshader.setVec3(std::format("light[{}].ambient", i), point_color[i] * glm::vec3(0.1));
			rockshader.setVec3(std::format("light[{}].diffuse", i), point_color[i] * glm::vec3(0.4));
			rockshader.setVec3(std::format("light[{}].specular", i), point_color[i]);
		}
		rockshader.setFloat("material.shininess", 16.0);
		rockshader.setFloat("lightstrength.constant", 1.0);
		rockshader.setFloat("lightstrength.linear", 0.09f);
		rockshader.setFloat("lightstrength.quadratic", 0.032f);

		rockshader.setVec3("sunlight.direction", -0.2f, -1.0f, -0.3f);
		rockshader.setVec3("sunlight.ambient", sunambient);
		rockshader.setVec3("sunlight.diffuse", sundiffuse);
		rockshader.setVec3("sunlight.specular", sunspecular);

		rockshader.setVec3("flashlight.direction", camera.Front);
		rockshader.setVec3("flashlight.position", camera.Position);
		rockshader.setFloat("flashlight.cutoff", glm::cos(glm::radians(12.5f)));
		rockshader.setFloat("flashlight.outer_cutoff", glm::cos(glm::radians(17.5f)));
		rockshader.setVec3("flashlight.ambient", 0.1f, 0.1f, 0.1f);
		rockshader.setVec3("flashlight.diffuse", 0.8f, 0.8f, 0.8f);
		rockshader.setVec3("flashlight.specular", lightColor);

		rockshader.setVec3("viewpos", camera.Position);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0, -5.0, 0.0));
		model = glm::scale(model, glm::vec3(10.0, 0.1, 10.0));
		rockshader.setMat4("model", model);
		rockshader.setMat4("view", view);
		rockshader.setMat4("projection", projection);

		rock.Draw(rockshader);

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