//
// Created by Wzeqiu on 2018/10/8.
//
#include "../utils/gl_utils.h"


static GLint programId[2];
static GLuint VAO[2], VBO[2];  // 顶点数组对象，顶点缓存对象


extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_shadder_Native_ShadderInitOpenGL(JNIEnv *env,
                                                                                jclass type) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    programId[0] = LinkProgram("shadder/uniform_vertex_shader.glsl", "shadder/uniform_frgment_shadder.glsl");
    programId[1] = LinkProgram("shadder/vertex_shader.glsl", "shadder/frgment_shadder.glsl");

    GLfloat LiftVertices[] = {
            -0.9f, -0.5f, 0.0f,  // left
            -0.0f, -0.5f, 0.0f,  // right
            -0.45f, 0.5f, 0.0f,  // top
    };
    GLfloat RightVertices[] = {
            0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // left
            0.9f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// right
            0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
    };

    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(LiftVertices), LiftVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) 0);
    glEnableVertexAttribArray(0);

    //*************************************************************
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(RightVertices), RightVertices, GL_STATIC_DRAW);
    /******************** start 数据传到顶点着色器   layout 接收 **********************/
    // 顶点
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) 0);
    glEnableVertexAttribArray(0);
    // 颜色
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    /******************** end 数据传到顶点着色器 **********************/
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

    // 修改着色器中的属性
    GLint vertexColor = glGetUniformLocation(programId[0], "ourColor");
    glUniform4f(vertexColor, 1.0f, 1.0f, 0.0f, 0.0f);

    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);


    glUseProgram(programId[1]);
    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // TODO

}

