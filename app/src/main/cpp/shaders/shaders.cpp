//
// Created by Wzeqiu on 2018/10/8.
//
#include "../utils/gl_utils.h"


static GLint programId[2];
static GLuint VAO, VBO;


extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_shadder_Native_ShadderInitOpenGL(JNIEnv *env,
                                                                                jclass type) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    programId[0] = LinkProgram("shadder/uniform_vertex_shader.glsl", "shadder/uniform_frgment_shadder.glsl");

    GLfloat LiftVertices[] = {
            -0.9f, -0.5f, 0.0f,  // left
            -0.0f, -0.5f, 0.0f,  // right
            -0.45f, 0.5f, 0.0f,  // top
    };
    GLfloat Vertices[] = {
            0.0f, -0.5f, 0.0f,  // left
            0.9f, -0.5f, 0.0f,  // right
            0.45f, 0.5f, 0.0f   // top
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(LiftVertices), LiftVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) 0);
    glEnableVertexAttribArray(0);
    // TODO
}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_shadder_Native_ShadderOnViewportChanged(JNIEnv *env,
                                                                                       jclass type,
                                                                                       jfloat width,
                                                                                       jfloat height) {
    glViewport(0, 0, width, height);
    // TODO
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_shadder_Native_ShadderRenderOneFrame(JNIEnv *env,
                                                                                    jclass type) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programId[0]);
    GLint vertexColor = glGetUniformLocation(programId[0], "ourColor");
    glUniform4f(vertexColor, 1.0f, 1.0f, 0.0f, 0.0f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // TODO

}

