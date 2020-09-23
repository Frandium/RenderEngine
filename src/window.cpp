#include "window.h"
#include <iostream>

Window* Window::s_ins = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window* Window::Instance() {
    if (s_ins == nullptr) {
        std::cout << "error: Call Window::Init first!" << std::endl;
    }
    return s_ins;
}

Window* Window::Init(float w, float h) {
    if (s_ins != nullptr) {
        std::cout << "warning: Window is already instantiated." << std::endl;
        return s_ins;
    }
    s_ins = new Window(w, h);
    return s_ins;
}

Window::Window(float w, float h):
    m_width(w),
    m_height(h)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(w, h, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    Input::SetWindow(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    glViewport(0, 0, w, h);
    glEnable(GL_DEPTH_TEST);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glClearColor(.8f, .8f, .8f, 1);

    
}

void Window::Delete() {
    glfwSetWindowShouldClose(window, true);
    
    glfwTerminate();
}

void Window::Render() {
    
    glDrawElements(GL_TRIANGLES, m_global_indices_count, GL_UNSIGNED_INT, 0);
       
}

void Window::Clear() {
    glfwSwapBuffers(window);
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}