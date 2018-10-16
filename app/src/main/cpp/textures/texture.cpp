//
// Created by Wzeqiu on 2018/10/9.
//
#include "../utils/gl_utils.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../utils/stb_image.h"

static GLint programID;
static GLuint VAO, VBO, EBO, texture1, texture2; // 顶点数组对象，顶点缓存对象，索引缓存对象,纹理
extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_textures_Native_TextureInitOpenGL(JNIEnv *env,
                                                                                 jclass type) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    programID = LinkProgram("textures/texture_vertex.glsl", "textures/texture_fragment.glsl");

    GLfloat vertices[] = {
            // positions          // colors           // texture coords
            0.5f, 0.5f, 0.0f,       1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f,      1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
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

    /******************** start 数据传到顶点着色器    layout 接收  **********************/
    // 顶点
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) 0);
    glEnableVertexAttribArray(0);
    // 颜色
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // 纹理坐标
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (void *) (6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    /******************** end 数据传到顶点着色器 **********************/

    // 记载纹理一
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    //纹理环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //纹理过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    GLboolean *data = stbi_load("/sdcard/MyOpenGLES1/assets/textures/container.jpg", &width,
                                &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        LOGE("加載纹理图片失败");
    }
    stbi_image_free(data);

    // 加载纹理二
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("/sdcard/MyOpenGLES1/assets/textures/awesomeface.png", &width, &height,
                     &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        LOGE("加載纹理图片失败");
    };
    stbi_image_free(data);



// TODO
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_textures_Native_TextureOnViewportChanged(JNIEnv *env,
                                                                                        jclass type,
                                                                                        jfloat width,
                                                                                        jfloat height) {
    glViewport(0, 0, width, height);

    // TODO

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_textures_Native_TextureRenderOneFrame(JNIEnv *env,
                                                                                     jclass type) {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    //自动把纹理赋值给片段着色器的采样器  片段着色器 通过采样器(Sampler) 接收


//    glBindTexture(GL_TEXTURE_2D, texture1);
    glUseProgram(programID);

    //着色器采样器属于哪个纹理单元 和绑定的纹理单元对应
    glUniform1i(glGetUniformLocation(programID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(programID, "texture2"), 1);

    // 绑定纹理到对应的纹理单元
    glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元
    glBindTexture(GL_TEXTURE_2D, texture1);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


    // TODO

}