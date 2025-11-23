#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "vertexObjects.hpp"

#include <iostream>

float verts[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f

};

int main(int argc, char *argv[]) {
    std::cout << "this is cool" << std::endl;

    GLFWwindow *window;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(1280, 720, "hello", NULL, NULL);

    glfwMakeContextCurrent(window);

    gladLoadGL(glfwGetProcAddress);

    glViewport(0, 0, 1280, 720);


    for(int i = 0; i < sizeof(verts)/sizeof(float); i += 3) {
        verts[i] -= 0.5;
    }


    VAO vao; //generates the vertex arrays
    VBO vbo(verts, sizeof(verts)); // generates buffer arrays, binds, binds buffer data

    vao.bind();
    vao.addAttrib(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    vao.unbind();
    vbo.unbind();


    for(int i = 0; i < sizeof(verts)/sizeof(float); i += 3) {
        verts[i] += 1.0f;
    }

    VAO vao2;
    VBO vbo2(verts, sizeof(verts));

    vao2.bind();
    vao2.addAttrib(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    vao2.unbind();
    vbo2.unbind();

    Shader vertShader("shaders/vert.glsl", GL_VERTEX_SHADER);
    Shader fragShader("shaders/frag.glsl", GL_FRAGMENT_SHADER);
    Shader frag2Shader("shaders/frag2.glsl", GL_FRAGMENT_SHADER);


    unsigned int program;
    unsigned int program2;

    createProgram(program2, vertShader, frag2Shader);
    createProgram(program, vertShader, fragShader);



    vertShader.destroy();
    fragShader.destroy();





    while(!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        glClearColor(0.3f, 0.8f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program);

        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, sizeof(verts)/sizeof(float));
        vao.unbind();

        glUseProgram(program2);

        vao2.bind();
        glDrawArrays(GL_TRIANGLES, 0, sizeof(verts)/sizeof(float));
        vao2.unbind();


        glfwSwapBuffers(window);
    }

    glfwTerminate();
}
