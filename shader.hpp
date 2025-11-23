#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include <glad/gl.h>

struct Shader {
    std::string filesrc;
    unsigned int shader;

    Shader(std::string filename, int type) {
        std::ifstream file(filename);
        std::string buffer;

        while(std::getline(file, buffer)) {
            filesrc.append(buffer);
            filesrc.push_back('\n');
        }

        shader = glCreateShader(type);

        const char *cSrc = filesrc.c_str();
        glShaderSource(shader, 1, &cSrc, NULL);
        glCompileShader(shader);


    }
    void destroy() {
        glDeleteShader(shader);
    }

};
void createProgram(unsigned int &program, Shader vert, Shader frag) {
    program = glCreateProgram();
    glAttachShader(program, vert.shader);
    glAttachShader(program, frag.shader);
    glLinkProgram(program);
}
