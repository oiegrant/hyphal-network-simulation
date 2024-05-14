// structures.h
#ifndef GEOMETRYUTILS_H
#define GEOMETRYUTILS_H


typedef struct vec2 {
    float x;
    float y;
} vec2;

typedef struct vec3 {
    float x;
    float y;
    float z;
} vec3;

typedef struct line {
    int shaderProgram;
    int VBO, VAO, texture_id;
    float *vertices;
    vec2 *startPoint;
    vec2 *endPoint;
    vec3 *lineColor;
} line;


#endif