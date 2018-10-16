//
// Created by Wzeqiu on 2018/10/16.
//
#include "../utils/gl_utils.h"
#include "../utils/stb_image.h"

#include "../utils/glm/glm.hpp"
#include "../utils/glm/gtc/matrix_transform.hpp"
#include "../utils/glm/gtc/type_ptr.hpp"

static GLuint programID;
static GLuint VAO, VBO, EBO;
static GLuint texture1, texture2;
static jfloat scr_width,scr_height;


extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_coordinate_Native_CoordinateInitOpenGL(
        JNIEnv env, jclass type) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    programID = LinkProgram("coordinate/texture_vertex.glsl", "coordinate/texture_fragment.glsl");

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

    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5* sizeof(GLfloat),(void*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glGenTextures(1,&texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    int width,height,nrChannels;
    GLboolean  *data=stbi_load("/sdcard/MyOpenGLES1/assets/coordinate/container.jpg",&width,&height,&nrChannels,0);
    if (data){
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        LOGE("coordinate  data is null");
    }
    stbi_image_free(data);

     glGenTextures(1,&texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
      data=stbi_load("/sdcard/MyOpenGLES1/assets/coordinate/awesomeface.png",&width,&height,&nrChannels,0);
    if (data){
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        LOGE("coordinate  data is null");
    }
    stbi_image_free(data);
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_coordinate_Native_CoordinateOnViewportChanged(
        JNIEnv env, jclass type, jfloat width, jfloat height) {
    scr_width=width;
    scr_height=height;
    glViewport(0, 0, width, height);

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_coordinate_Native_CoordinateRenderOneFrame(
        JNIEnv env, jclass type) {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glUseProgram(programID);
    glUniform1i(glGetUniformLocation(programID,"texture1"),0);
    glUniform1i(glGetUniformLocation(programID,"texture2"),1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture1);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,texture2);

    glm::mat4 model=glm::mat4(1.0f);
    glm::mat4 view=glm::mat4(1.0f);
    glm::mat4 projection=glm::mat4(1.0f);

    model=glm::rotate(model,glm::radians(-55.0f),glm::vec3(1.0f, 0.0f, 0.0f));
    view=glm::translate(view,glm::vec3(0.0f, 0.0f, -3.0f));
    projection=glm::perspective(glm::radians(45.0f),scr_width/scr_height,0.1f,100.0f);

    glUniformMatrix4fv(glGetUniformLocation(programID,"model"),1,GL_FALSE,glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(programID,"view"),1,GL_FALSE,glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(programID,"projection"),1,GL_FALSE,glm::value_ptr(projection));



    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}