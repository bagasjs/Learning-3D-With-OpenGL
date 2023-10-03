#include "Shader.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Texture2D.hpp"
#include "glm/ext/matrix_clip_space.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void CheckOpenGLError(bool exit_on_error)
{
    GLenum err = GL_NO_ERROR;
    std::cout << "CHECKING OPENGL ERROR" << std::endl;
    while((err = glGetError()) != GL_NO_ERROR) {
        if(err == GL_NO_ERROR) {
            break;
        } else {
            if(err == GL_INVALID_ENUM) {
                std::cerr << "OPENGL ERROR: GL_INVALID_ENUM" << std::endl;
            } else if(err == GL_INVALID_VALUE) {
                std::cerr << "OPENGL ERROR: GL_INVALID_VALUE" << std::endl;
            } else if(err == GL_INVALID_OPERATION) {
                std::cerr << "OPENGL ERROR: GL_INVALID_OPERATION" << std::endl;
            } else if(err == GL_STACK_OVERFLOW) {
                std::cerr << "OPENGL ERROR: GL_STACK_OVERFLOW" << std::endl;
            } else if(err == GL_STACK_UNDERFLOW) {
                std::cerr << "OPENGL ERROR: GL_STACK_UNDERFLOW" << std::endl;
            } else if(err == GL_OUT_OF_MEMORY) {
                std::cerr << "OPENGL ERROR: GL_OUT_OF_MEMORY" << std::endl;
            } else if(err == GL_INVALID_FRAMEBUFFER_OPERATION) {
                std::cerr << "OPENGL ERROR: GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
            } else {
                std::cerr << "OPENGL ERROR:" << std::endl;
            }
            if(exit_on_error) exit(EXIT_FAILURE);
        }
    }
}

int main(void) {
    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello, World", 0, 0);
    if(!window) {
        std::cerr << "Failed to create Window" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to load opengl functions" << std::endl;
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glEnable(GL_DEPTH_TEST);

    uint32_t vaoID = 0;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    uint32_t vboID = 0;
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        +0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        +0.5f, +0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        +0.5f, +0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, +0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, +0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        +0.5f, -0.5f, +0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        +0.5f, +0.5f, +0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        +0.5f, +0.5f, +0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, +0.5f, +0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, +0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, +0.5f, +0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, +0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, +0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, +0.5f, +0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        +0.5f, +0.5f, +0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        +0.5f, +0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        +0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        +0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        +0.5f, -0.5f, +0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        +0.5f, +0.5f, +0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        +0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        +0.5f, -0.5f, +0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        +0.5f, -0.5f, +0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, +0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, +0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        +0.5f, +0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        +0.5f, +0.5f, +0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        +0.5f, +0.5f, +0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, +0.5f, +0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, +0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    };

    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*9, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float)*9, (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float)*9, (void*)(7*sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode

    std::string vertSrcPath = "./resources/basic.vert";
    std::string fragSrcPath = "./resources/basic.frag";
    Shader shader = Shader::CreateFromFile(vertSrcPath, fragSrcPath);
    if(shader.IsError()) {
        std::cerr << "SHADER CREATION ERROR " << shader.Why();
        exit(EXIT_FAILURE);
    }

    uint32_t eboID;
    uint32_t elements[] = {
        0, 1, 2, 2, 3, 0,
    };
    glGenBuffers(1, &eboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    shader.Enable();
    if(shader.GetUniformLocation("u_Proj") < 0) {
        std::cerr << "Invalid uniform " << "u_Proj" << std::endl;
    }
    if(shader.GetUniformLocation("u_View") < 0) {
        std::cerr << "Invalid uniform " << "u_View" << std::endl;
    }
    if(shader.GetUniformLocation("u_Model") < 0) {
        std::cerr << "Invalid uniform " << "u_Model" << std::endl;
    }


    glm::mat4 uProj = glm::mat4(1.0f);
    glm::mat4 uModel = glm::mat4(1.0f);
    glm::mat4 uView = glm::mat4(1.0f);
    uProj = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 
            0.1f, 100.0f);
    shader.SetUniform("u_Proj", Shader::Type::MAT4, 1, glm::value_ptr(uProj), false);

    int width, height, channels;
    width = height = channels = 0;
    stbi_uc* data = stbi_load("./resources/bricks.jpg", &width, &height, &channels, 0);
    Texture2D texture((int8_t*)data, width, height, channels);

    if(shader.GetUniformLocation("u_TextureSamplers") < 0) {
        std::cerr << "Invalid uniform " << "u_TextureSamplers" << std::endl;
    }
    texture.Enable(1);
    int samplers[] = { 1 };
    shader.SetUniform("u_TextureSamplers", Shader::Type::INT, 1, &samplers, false);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        uModel = glm::rotate(glm::mat4(1.0), (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(1.0f, 0.35f, 0.6f));
        uView = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        shader.SetUniform("u_View", Shader::Type::MAT4, 1, glm::value_ptr(uView), false);
        shader.SetUniform("u_Model", Shader::Type::MAT4, 1, glm::value_ptr(uModel), false);

        glBindVertexArray(vaoID);
        shader.Enable();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // glDrawElements(GL_TRIANGLES, sizeof(elements)/sizeof(uint32_t), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
