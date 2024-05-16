#include <testRender.hpp>

#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>



void testRender::create_lines() {
    
    std::vector<GLfloat> vertices;
    vertices.reserve(drawData.size() * 6); // Pre-allocate space for all vertices

    // Convert coordinates to OpenGL's normalized device coordinates (NDC)
    for (const auto& line : drawData) {
        if (line.size() < 4) {
            std::cerr << "Skipping invalid line data." << std::endl;
            continue; // Skip incomplete data
        }
        
        //TODO update the screen width to be dynamic?
        //This sets the vertices to be between -1/+1
        float x1 = static_cast<float>(line[0]) / 400.0f - 1.0f; // Assuming 800 is the width of the screen
        float y1 = static_cast<float>(line[1]) / 300.0f - 1.0f; // Assuming 600 is the height of the screen
        float x2 = static_cast<float>(line[2]) / 400.0f - 1.0f;
        float y2 = static_cast<float>(line[3]) / 300.0f - 1.0f;

        // First endpoint (x1, y1, 0)
        vertices.push_back(x1);
        vertices.push_back(y1);
        vertices.push_back(0.0f);

        // Second endpoint (x2, y2, 0)
        vertices.push_back(x2);
        vertices.push_back(y2);
        vertices.push_back(0.0f);
    }

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void testRender::add_shader(GLuint program, const char* shader_code, GLenum type) {
    GLuint current_shader = glCreateShader(type);
    const GLchar* code[1] = {shader_code};
    GLint code_length[1] = {static_cast<GLint>(strlen(shader_code))};
    glShaderSource(current_shader, 1, code, code_length);
    glCompileShader(current_shader);

    GLint result = 0;
    GLchar log[1024] = {0};

    glGetShaderiv(current_shader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(current_shader, sizeof(log), NULL, log);
        std::cout << "Error compiling " << type << " shader: " << log << "\n";
        return;
    }

    glAttachShader(program, current_shader);
}

void testRender::create_shaders() {
    shader = glCreateProgram();
    if (!shader) {
        std::cout << "Error creating shader program!\n";
        exit(1);
    }

    add_shader(shader, vertex_shader_code, GL_VERTEX_SHADER);
    add_shader(shader, fragment_shader_code, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar log[1024] = {0};

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(log), NULL, log);
        std::cout << "Error linking program:\n" << log << '\n';
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(log), NULL, log);
        std::cout << "Error validating program:\n" << log << '\n';
        return;
    }

    // Retrieve uniform locations
    projMatrixLoc = glGetUniformLocation(shader, "projectionMatrix");
    viewMatrixLoc = glGetUniformLocation(shader, "viewMatrix");
    if (projMatrixLoc == -1 || viewMatrixLoc == -1) {
        std::cout << "Error finding uniform locations.\n";
    }
}

void testRender::create_framebuffer() {
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void testRender::bind_framebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void testRender::unbind_framebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void testRender::rescale_framebuffer(float width, float height) {
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
}

void testRender::initialize(GLFWwindow* window) {

    this->window = window; // Store the GLFWwindow pointer in your class
    glfwSetWindowUserPointer(window, this); // Set this as user pointer
    create_lines();
    create_shaders();
    create_framebuffer();

    // Set GLFW callbacks
    glfwSetScrollCallback(window, scroll_callback);
}

void testRender::handleMouseScroll(float offset) {
    zoomFactor *= (1.0f + offset * 0.05f);
}

void testRender::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    testRender* render = static_cast<testRender*>(glfwGetWindowUserPointer(window));
    if (render && !ImGui::GetIO().WantCaptureMouse) {
        render->mouseScrolled = true;
        render->scrollOffset = static_cast<float>(yoffset);
    }
}

void testRender::update_matrices() {
    projectionMatrix = glm::perspective(glm::radians(45.0f * zoomFactor), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(rotationX), glm::vec3(1, 0, 0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(rotationY), glm::vec3(0, 1, 0));
}

void testRender::cleanup() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteFramebuffers(1, &FBO);
    glDeleteRenderbuffers(1, &RBO);
    glDeleteTextures(1, &texture_id);
    glDeleteProgram(shader);
}

void testRender::render() {
    update_matrices();
    
    bind_framebuffer();
    glUseProgram(shader);
    glBindVertexArray(VAO);
    
    glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    glDrawArrays(GL_LINES, 0, drawData.size()*2);
    glBindVertexArray(0);
    glUseProgram(0);
    unbind_framebuffer();
}
