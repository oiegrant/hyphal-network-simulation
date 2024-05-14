#include <testRender_lines.hpp>
#include <geometryUtil.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

vec2* testRender_lines::vec2_init(float _x, float _y) {
    vec2 *v = (vec2*)malloc(sizeof(vec2));
    v->x = _x;
    v->y = _y;
    return v;
}

vec3* testRender_lines::vec3_init(float _x, float _y, float _z) {
    vec3 *v = (vec3*)malloc(sizeof(vec3));
    v->x = _x;
    v->y = _y;
    v->z = _z;
    return v;
}


// Utility function to create and configure a line object
line* testRender_lines::initialize_line(vec2 *start, vec2 *end) {
    
    line *l = (line*)malloc(sizeof(line));

    float x1 = start->x;
    float y1 = start->y;
    float x2 = end->x;
    float y2 = end->y;
    float w = SCR_WIDTH;
    float h = SCR_HEIGHT;
 
    // convert 3d world space position 2d screen space position
    x1 = 2*x1 / w - 1;
    y1 = 2*y1 / h - 1;
 
    x2 = 2*x2 / w - 1;
    y2 = 2*y2 / h - 1;
 
    start->x = x1;
    start->y = y1;
    end->x = x2;
    end->y = y2;

    l->startPoint = start;
    l->endPoint = end;
    l->lineColor = vec3_init(1.0f,1.0f,1.0f);

    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec3 color;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(color, 1.0f);\n"
        "}\n\0";

    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // link shaders
    l->shaderProgram = glCreateProgram();
    glAttachShader(l->shaderProgram, vertexShader);
    glAttachShader(l->shaderProgram, fragmentShader);
    glLinkProgram(l->shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // setting vertex data
    l->vertices = (float*)(malloc(sizeof(float) * 6));
    l->vertices[0] = start->x;
    l->vertices[1] = start->y;
    l->vertices[2] = end->x;
    l->vertices[3] = end->y;

    glGenVertexArrays(1, &l->VAO);
    glGenBuffers(1, &l->VBO);
    glBindVertexArray(l->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, l->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(l->vertices)*4,
                                  &l->vertices[0],
                                  GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                            2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    return l;
}

void testRender_lines::rescale_framebuffer(float width, float height) {
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

    // glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
}



std::vector<line*> testRender_lines::line_init(const std::vector<std::vector<int>>& coordinates) {

    std::vector<line*> lines;

    for (const auto& coords : coordinates) {
        if (coords.size() < 4) {
            continue; // Skip incomplete rows
        }

        vec2* start = vec2_init(static_cast<float>(coords[0]), static_cast<float>(coords[1]));
        vec2* end = vec2_init(static_cast<float>(coords[2]), static_cast<float>(coords[3]));
        
        line* l = initialize_line(start, end);
        lines.push_back(l);
    }

    return lines;
}

int testRender_lines::line_draw(const std::vector<line*> &lines) {
    for (line* l : lines) {
        glUseProgram(l->shaderProgram);

        // Assuming lineColor is a member of type vec3 in struct line
        glUniform3fv(glGetUniformLocation(l->shaderProgram, "color"), 1, &l->lineColor->x);

        glBindVertexArray(l->VAO);
        glDrawArrays(GL_LINES, 0, 2);
    }
    return 0;
}

// int main(int argc, char *argv[])
// {
//     if (glfwInit() != GL_TRUE) {
//         fputs("Failed to initialize GLFW\n", stderr);
//         return EXIT_FAILURE;
//     }

//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

//     GLFWwindow* window = glfwCreateWindow(640, 480, "Example",0,0);
//     glfwMakeContextCurrent(window);

//     glewExperimental = GL_TRUE;
//     if (glewInit() != GLEW_OK) {
//         fputs("Failed to initialize GLEW\n", stderr);
//         return EXIT_FAILURE;
//     }

//     line *line1 = line_init(vec2_init(100,100), vec2_init(100,200));
//     line *line2 = line_init(vec2_init(200,100), vec2_init(400,150));
//     line *line3 = line_init(vec2_init(400,600), vec2_init(600,400));
//     line *line4 = line_init(vec2_init(300,300), vec2_init(500,100));
//     line *line5 = line_init(vec2_init(600,50) , vec2_init(400,100));
//     line *line6 = line_init(vec2_init(400,400), vec2_init(800,600));

//     while (!glfwWindowShouldClose(window)) {

//         if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//             glfwSetWindowShouldClose(window, 1);

//         glClearColor(0.0, 0.0, 0.0, 1.0);
//         glClear(GL_COLOR_BUFFER_BIT);
 
//         line_draw(line1);
//         line_draw(line2);
//         line_draw(line3);
//         line_draw(line4);
//         line_draw(line5);
//         line_draw(line6);

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glfwTerminate();
//     return EXIT_SUCCESS;
// }