#ifndef TESTRENDER_LINES_HPP
#define TESTRENDER_LINES_HPP

#include <geometryUtil.hpp>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class testRender_lines {
    public:
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    vec2* vec2_init(float _x, float _y);
    vec3* vec3_init(float _x, float _y, float _z);
    line* initialize_line(vec2 *start, vec2 *end);
    void rescale_framebuffer(float width, float height);
    std::vector<line*> line_init(const std::vector<std::vector<int>> &input);
    int line_draw(const std::vector<line*>& lines);
};
#endif // TESTRENDER_LINES_HPP
