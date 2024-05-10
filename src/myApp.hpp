#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace myApp 
{   
    int RenderUI();
    int RenderUI_2();
    void processInput(GLFWwindow *window);
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void displayLine(GLint vertexData[][4], int numVertices);
    void initialize();
    void cleanup();
    void render();
    void rescale_framebuffer(float width, float height);
    void create_triangle();
    void create_shaders();
    void create_framebuffer();
    void bind_framebuffer();
    void unbind_framebuffer();
    void add_shader(GLuint program, const char* shader_code, GLenum type);
}