#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef TEST_RENDER
#define TEST_RENDER

#include <iostream>
#include <vector>
using namespace std;

class testRender {
    public:
        const GLint WIDTH = 800;
        const GLint HEIGHT = 600;
        GLuint VAO, VBO, FBO, RBO, texture_id, shader;
        std::vector<std::vector<int>> drawData;

        //IO variables
        float zoomFactor = 1.0f;
        float rotationX = 0.0f;
        float rotationY = 0.0f;
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        GLFWwindow* window;
        GLint projMatrixLoc, viewMatrixLoc;
        bool mouseScrolled = false;
        float scrollOffset = 0.0f;

        testRender() {}
        ~testRender() {}
        void hello() { cout << "HELLO\n";}
        void initialize(GLFWwindow* window);
        void cleanup();
        void render();
        void rescale_framebuffer(float width, float height);
        void create_lines();
        void create_lines(const std::vector<std::vector<int>>& lines);
        void create_triangle();
        void create_shaders();
        void create_framebuffer();
        void bind_framebuffer();
        void unbind_framebuffer();
        void add_shader(GLuint program, const char* shader_code, GLenum type);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        void update_matrices();
        void handleMouseScroll(float offset);

        const char* vertex_shader_code = R"*(
            #version 330
            layout (location = 0) in vec3 pos;

            uniform mat4 projectionMatrix;
            uniform mat4 viewMatrix;

            void main() {
                gl_Position = projectionMatrix * viewMatrix * vec4(pos, 1.0);
            }
        )*";

        const char* fragment_shader_code = R"*(
            #version 330
            out vec4 color;

            void main() {
                color = vec4(0.0, 1.0, 0.0, 1.0);
            }
        )*";
};

#endif