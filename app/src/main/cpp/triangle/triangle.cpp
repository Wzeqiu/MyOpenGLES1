#include "../utils/gl_utils.h"

static GLuint VBO[2], VAO[2]; // 顶点数组对象，顶点缓存对象
static GLuint programId[2];

extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_triangle_Native_TriangleInitOpenGL(JNIEnv *env,
                                                                                  jclass type) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    programId[0] = LinkProgram("triangle/vertex_shader.glsl", "triangle/blue_fragment_shader.glsl");
    programId[1] = LinkProgram("triangle/vertex_shader.glsl", "triangle/yellow_fragment_shader.glsl");


//    GLfloat vVertices[] = {
//            0.0f, 0.5f, 0.0f,
//            -0.5f, -0.5f, 0.0f,
//            0.5f, -0.5f, 0.0f};

    GLfloat blueVertices[] = {
            0.0f, -0.5f, 0.0f,  // left
            0.9f, -0.5f, 0.0f,  // right
            0.45f, 0.5f, 0.0f   // top
    };
    GLfloat yellowVertices[] = {
            -0.9f, -0.5f, 0.0f,  // left
            -0.0f, -0.5f, 0.0f,  // right
            -0.45f, 0.5f, 0.0f,  // top
    };

    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(blueVertices), blueVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) 0);
    glEnableVertexAttribArray(0);


    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(yellowVertices), yellowVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) 0);
    glEnableVertexAttribArray(0);


}extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_triangle_Native_TriangleOnViewportChanged(
        JNIEnv *env, jclass type,
        jfloat width,
        jfloat height) {
    glViewport(0, 0, width, height);

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_triangle_Native_TriangleRenderOneFrame(JNIEnv *env,
                                                                                      jclass type) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programId[0]);

    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(programId[1]);
    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
}

