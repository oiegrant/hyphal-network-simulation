#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace myApp 
{   
    int render();
    void processInput(GLFWwindow *window);
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void displayLine(GLint vertexData[][4], int numVertices);
}