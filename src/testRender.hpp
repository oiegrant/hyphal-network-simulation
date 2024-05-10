#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef TEST_RENDER
#define TEST_RENDER

#include <iostream>
using namespace std;

class testRender {
    public:
        const GLint WIDTH = 800;
        const GLint HEIGHT = 600;
        GLuint VAO, VBO, FBO, RBO, texture_id, shader;

        testRender() {}
        ~testRender() {}
        void hello() { cout << "HELLO\n";}
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

        const char* vertex_shader_code = R"*(
        #version 330
        layout (location = 0) in vec3 pos;
        void main() {
            gl_Position = vec4(0.9*pos.x, 0.9*pos.y, 0.5*pos.z, 1.0);
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