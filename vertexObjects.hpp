#pragma once
#include <glad/gl.h>

struct VBO {
    unsigned int ID;

    VBO(const float *verts, int size) {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);

    }

    void bind() {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }
    void unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

};

struct VAO {
    unsigned int ID;

    VAO() {
        glGenVertexArrays(1, &ID);
    }
    void bind() {
        glBindVertexArray(ID);
    }
    void unbind() {
        glBindVertexArray(0);
    }
    void addAttrib(int index,
                   int size,
                   int type,
                   unsigned char normalized,
                   int stride,
                   void *offset) {
        bind();
        glVertexAttribPointer(index, size, type, normalized, stride, offset);
        glEnableVertexAttribArray(index);
    }
};
