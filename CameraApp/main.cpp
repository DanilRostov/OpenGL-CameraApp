//
//  main.cpp
//  CameraApp
//
//  Created by Danil Rostov on 4/21/25.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "camera.hpp"
#include "mesh.hpp"

Camera* gCamera = nullptr;  // Global camera pointer

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);

GLuint createShaderProgram()
{
    const char *vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aColor;
        out vec3 vColor;
        uniform mat4 uProjection;
        uniform mat4 uView;
        uniform mat4 uModel;
    
        void main() {
            vColor = aColor;
            gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
        }
    )";

    const char *fragmentShaderSource = R"(
        #version 330 core
        in vec3 vColor;
        out vec4 FragColor;
        void main() {
            FragColor = vec4(vColor, 1.0);
        }
    )";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Camera", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }
    
    glEnable(GL_DEPTH_TEST);

    GLuint shaderProgram = createShaderProgram();
    
    // Setup camera
    Camera camera;
    camera.lookAt(
        glm::vec3(2.0f, 2.0f, 2.0f),   // eye from top-right corner
        glm::vec3(0.0f, 0.0f, 0.0f),   // center
        glm::vec3(0.0f, 1.0f, 0.0f)    // up
    );
    gCamera = &camera;  // Assign global camera pointer

    // Setup mesh
    Mesh mesh;
    mesh.init();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uModel"), 1, GL_FALSE, glm::value_ptr(model));
        
        camera.apply(shaderProgram);
        
        mesh.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    mesh.cleanup();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (gCamera) gCamera->onMouseDown(static_cast<int>(xpos), static_cast<int>(ypos));
    }
    
    if (action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (gCamera) gCamera->setDragging(false);
    }
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (gCamera)
        gCamera->onMouseMove(static_cast<int>(xpos), static_cast<int>(ypos));
}
