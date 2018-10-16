//
// Created by Wzeqiu on 2018/10/15.
//

#include "../utils/gl_utils.h"
#include "../utils/glm/glm.hpp"
#include "../utils/glm/gtc/matrix_transform.hpp"
#include "../utils/glm/gtc/type_ptr.hpp"

//#define STB_IMAGE_IMPLEMENTATION

#include "../utils/stb_image.h"

static GLuint programID;
static GLuint VAO, VBO, EBO;
static GLuint texture1, texture2;

extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_positionchange_Native_PositionChanageInitOpenGL(
        JNIEnv *env, jclass type) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    programID = LinkProgram("position_change/texture_vertex.glsl",
                            "position_change/texture_fragment.glsl");

    GLfloat vertices[] = {
            // positions          // texture coords
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f  // top left
    };

    GLuint indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);


    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    GLboolean *data = stbi_load("/sdcard/MyOpenGLES1/assets/position_change/container.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        LOGE("textImage is null");
    }
    stbi_image_free(data);
//
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("/sdcard/MyOpenGLES1/assets/position_change/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        LOGE("textImage is null");
    }
    stbi_image_free(data);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_positionchange_Native_PositionChanageOnViewportChanged(
        JNIEnv *env, jclass type, jfloat width, jfloat height) {
    glViewport(0, 0, width, height);


}extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_positionchange_Native_PositionChanageRenderOneFrame(
        JNIEnv *env, jclass type) {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glUseProgram(programID);

    glUniform1i(glGetUniformLocation(programID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(programID, "texture2"), 1);

    glm::mat4 transform =glm::mat4(1.0f);

    // 旋转90
    transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
//    transform = glm::rotate(transform,(float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
    // 缩小0.5
    transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));
    // 平移
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));

    GLuint transformLoc = glGetUniformLocation(programID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    // 绑定纹理到对应的纹理单元
    glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元
    glBindTexture(GL_TEXTURE_2D, texture1);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}


