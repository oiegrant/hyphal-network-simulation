#include <GL/glut.h>

#ifndef TEST_RENDER
#define TEST_RENDER

#include <iostream>
using namespace std;

class testRender {
    public:
        testRender() {}
        ~testRender() {}
        void displayLine(GLint vertexData[][4], int numVertices);

};

#endif