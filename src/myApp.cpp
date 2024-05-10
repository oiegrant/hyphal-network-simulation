#include <myApp.hpp>
#include <iostream>

const GLint WIDTH = 800;
    const GLint HEIGHT = 600;
    GLuint VAO, VBO, FBO, RBO, texture_id, shader;

    // unsigned int VBO;
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

    
    
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    

namespace myApp 
{
    int RenderUI() {
        ImGui::BeginChild("Viewport");


        // glfwInit();
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


        GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // Initialize GLEW
        if (glewInit() != GLEW_OK) {
            return -1;
        }

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
         // fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // link shaders
        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left  
            0.5f, -0.5f, 0.0f, // right 
            0.0f,  0.5f, 0.0f  // top   
        }; 

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0); 

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0); 

        // uncomment this call to draw in wireframe polygons.
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)



        // glViewport(0, 0, 800, 600);


        while (!glfwWindowShouldClose(window))
        {
            // keyboard input
            processInput(window); // need to implement

            // render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // draw our first triangle
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawArrays(GL_TRIANGLES, 0, 3);
            // glBindVertexArray(0); // no need to unbind it every time 
    
            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        ImGui::EndChild();

        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
        return 0;
        
        // ImGui::EndChild();
    } //end render

    int RenderUI_2(){
        
        initialize();
        // create_triangle();
        // create_shaders();
        // create_framebuffer();

        ImGui::Begin("RenderUI_2");
        // const float window_width = ImGui::GetContentRegionAvail().x;
		// const float window_height = ImGui::GetContentRegionAvail().y;

        // rescale_framebuffer(window_width, window_height);
		// glViewport(0, 0, window_width, window_height);

        
        // ImVec2 pos = ImGui::GetCursorScreenPos();

        // ImGui::GetWindowDrawList()->AddImage(
		// 	(void *)texture_id, 
		// 	ImVec2(pos.x, pos.y), 
		// 	ImVec2(pos.x + window_width, pos.y + window_height), 
		// 	ImVec2(0, 1), 
		// 	ImVec2(1, 0)
		// );

        ImGui::Button("HELP");
        ImGui::End();
        return 0;

    }

    void processInput(GLFWwindow *window) {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
    
    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    void create_triangle() {
        GLfloat vertices[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        };

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void add_shader(GLuint program, const char* shader_code, GLenum type) {
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

    void create_shaders() {
        shader = glCreateProgram();
        if (!shader) {
            std::cout << "Error creating shader program!\n";
            exit(1);
        }

        add_shader(shader, vertexShaderSource, GL_VERTEX_SHADER);
        add_shader(shader, fragmentShaderSource, GL_FRAGMENT_SHADER);

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
    }

    void create_framebuffer() {
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

    void bind_framebuffer() {
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    }

    void unbind_framebuffer() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void rescale_framebuffer(float width, float height) {
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
    }

    void initialize() {
        create_triangle();
        create_shaders();
        create_framebuffer();
    }

    void cleanup() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteFramebuffers(1, &FBO);
        glDeleteRenderbuffers(1, &RBO);
        glDeleteTextures(1, &texture_id);
        glDeleteProgram(shader);
    }

    void render() {
        bind_framebuffer();
        // Placeholder: you might want to setup viewport, clear buffers, etc.
        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3); // Assumes you are drawing a simple triangle
        unbind_framebuffer();
    }

}