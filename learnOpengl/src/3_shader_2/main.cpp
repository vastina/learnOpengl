
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <windows.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const static double pi = 3.1415926;
const static double sqrt3 = 1.7320508;

const char* vertexShaderSource =
"#version 420 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 acolor;\n"
"out vec3 point_color;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos, 1.0f);\n"
"point_color = acolor;\n"
"}\0";//"gl_PointSize = 2.0f;\n"

const char* fragmentShaderSource =
"#version 420 core\n"
"out vec4 FragColor;\n"
"in vec3 point_color;\n"
"void main()\n"
"{\n"
"FragColor = vec4(point_color,1.0f);\n"
"}\0";

int main()
{
    std::cout << GL_MAX_VERTEX_ATTRIBS << std::endl;
    glfwInit();

    // 创建窗口对象
    GLFWwindow* window = glfwCreateWindow(800, 800, "w", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // 设置视口
    glViewport(0, 0, 800, 600);
    glEnable(GL_PROGRAM_POINT_SIZE);

    // 注册窗口变化监听
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 定义顶点数组
    double time = glfwGetTime();
    float f[3] = { sin(time) / 2.0f + 0.5f ,sin(time + pi * 2.0 / 3.0) / 2.0f + 0.5f,sin(time + pi * 4.0 / 3.0) / 2.0f + 0.5f };
    float vertices[] = {
        // 第一个三角形
        -0.25*sqrt3,0.25f,0.0f, f[0], 0.0f, 0.0f,
         0.25*sqrt3,0.25f,0.0f, 0.0f, f[1], 0.0f,
         0.0f,1.0f,0.0f       , 0.0f, 0.0f, f[2]

        // 第二个三角形
        //0.5f,0.5f,0.0f,
        //0.75,-0.5,0.0f,
        //0.25,-0.5,0.0f,
    };

    // 创建顶点和片段着色器
    unsigned int vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // 附加着色器代码
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // 创建程序对象
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // 将着色器附加到程序对象上
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
  
    // 链接
    glLinkProgram(shaderProgram);

    // 删除着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 创建缓冲对象
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);

    // 绑定VAO缓冲对象
    glBindVertexArray(VAO);
    // 绑定VBO缓对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 填充VBO数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    // 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(VAO);

    glBindVertexArray(0);
    // 设置线框绘制模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.5f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        time = glfwGetTime();
        f[0] = sin(time )/2.0f + 0.5f; f[1] = sin(time+pi*2.0/3.0)/2.0f + 0.5f; f[2] = sin(time + pi * 4.0 / 3.0) / 2.0f + 0.5f;
        float vertices[] = {
            -0.25 * sqrt3 + 0.5 * cos(time),0.5 * sin(time) - 0.25f,0.0f, f[0], 0.0f, 0.0f,
             0.25 * sqrt3 + 0.5 * cos(time),0.5 * sin(time) - 0.25f,0.0f, 0.0f, f[1], 0.0f,
             0.5*cos(time), 0.5*sin(time)+0.5,0.0f                       , 0.0f, 0.0f, f[2]
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

        glUseProgram(shaderProgram);

        //int vertex_color_location =  glGetUniformLocation(shaderProgram, "out_color");
        //glUniform4f(vertex_color_location, f[0], f[1], f[2], 1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawArrays(GL_POINTS, 0, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
