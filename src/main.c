#include <stdio.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>



void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);  

const char *vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos; \n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *fragmentShaderSource = 
"#version 330 core\n"
"out vec4 FragColor; \n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

float vertices[] = {
     -0.5f,  0.5f, 0.0f,  // top right
     0.5f, 0.5f, 0.0f,  // bottom right
     0.0f, -0.5f, 0.0f,  // bottom left
    -1.0f,  -0.5f, 0.0f,   // top left
    1.0f,  -0.5f, 0.0f   // top left
};




unsigned int indices[] = {  // note that we start from 0!
    0, 2, 3,   // first triangle
    1, 2, 4    // second triangle
};  


int main(){




    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
        {
            printf("Failed to create GLFW window\n");
            glfwTerminate();
            return -1;
        }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            printf("Failed to initialize GLAD\n");
            return -1;
        }  

    



    //compile the vertex shader 

    unsigned int vertexShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //check if we succesfully compile our shader language

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s", infoLog);
    }   

    //compile the shader language

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int  successfrag;
    char infoLogfrag[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successfrag);

    if(!successfrag)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogfrag);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED %s \n", infoLogfrag);
    }   

    //create a shaderprogram to link all multiple shaders

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int  successprog;
    char infoLogprog[512];
    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &successprog);

    if(!successprog)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLogprog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED %s \n",infoLogprog);

    }  

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    //Create vertex buffer object for the vertices


    unsigned int VAO;
    glGenVertexArrays(1, &VAO);


    //indices for vertices so we dont write vertices that overlap with eachother
    //creates overhead (Extra useless information)
    unsigned int EBO;
    glGenBuffers(1, &EBO);


    


    // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Must bind after creating vertexarraybuffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
 

    

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 



    while(!glfwWindowShouldClose(window))
        {
            processInput(window);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            

            glfwSwapBuffers(window);
            glfwPollEvents();    
        }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }  

void processInput(GLFWwindow *window)
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
