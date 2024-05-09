#include <testRender.hpp>

void testRender::displayLine(GLint vertexData[][4], int numVertices) {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0f, 0.0f, 1.0f); // Set color to blue

  glBegin(GL_LINES);
  for (int i = 0; i < numVertices - 1; ++i) {
    glVertex2i(vertexData[i][0], vertexData[i][1]); // Access x and y from vertex
    glVertex2i(vertexData[i + 1][0], vertexData[i + 1][1]); // Access next vertex
  }
  glEnd();
  glFlush();
}