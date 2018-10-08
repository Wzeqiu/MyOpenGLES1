//
// Created by Wzeqiu on 2018/10/8.
//

#include "gl_utils.h"

AAssetManager *aAssetManager = nullptr;

extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_UtilsNative_InitAsseManager(JNIEnv *env, jclass type,
                                                                      jobject am) {
    aAssetManager = AAssetManager_fromJava(env, am);
    if (aAssetManager == NULL) {
        LOGE(" InitAsseManager aAssetManager is %s", "aAssetManager==NULL");
        return;
    }
}

char *readShaderBuff(AAssetManager *aAssetManager, const char *filename) {
    LOGE(" shader file name is %s", filename);
    if (aAssetManager == NULL) {
        LOGE(" getbuff aAssetManager is aAssetManager==NULL");
        return NULL;
    }
    AAsset *asset = AAssetManager_open(aAssetManager, filename, AASSET_MODE_UNKNOWN);
    if (asset == NULL) {
        LOGE(" AAssetManager_open  asset==NULL");
        return NULL;
    }
    off_t bufferSize = AAsset_getLength(asset);
    LOGI(" asset size        : %ld\n", bufferSize);
    char *buffer = new char[bufferSize + 1];
    buffer[bufferSize] = '\0';
    int numByteRead = AAsset_read(asset, buffer, bufferSize);
    LOGI(" numByteRead        : %d\n", numByteRead);
    LOGI(" read buffer is :%s", buffer);
    return buffer;
}


GLuint LoadShader(GLenum type, const char *shaderSrc) {
    GLuint shader;
    GLint compiled;
    shader = glCreateShader(type);
    if (shader == 0) {
        LOGE("create shader is fail type : %d==", type);
        return 0;
    }
    glShaderSource(shader, 1, &shaderSrc, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 0) {
            char *infoLog = new char[sizeof(char) + infoLen];
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            LOGE("glShaderSource log is : %s", infoLog);
            delete[] infoLog;
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}


GLuint LoadVertexShader(AAssetManager *aAssetManager, const char *filename) {
    char *vertex_shader = readShaderBuff(aAssetManager, filename);
    GLuint vertex = LoadShader(GL_VERTEX_SHADER, vertex_shader);
    delete vertex_shader;
    return vertex;
}

GLuint LoadFragmentShader(AAssetManager *aAssetManager, const char *filename) {
    char *fragment_shader = readShaderBuff(aAssetManager, filename);
    GLuint fragment = LoadShader(GL_FRAGMENT_SHADER, fragment_shader);
    delete fragment_shader;
    return fragment;
}

GLuint LinkProgram(char *vertex, char *fragment) {
    GLint linked;
    // Load the vertex/fragment shaders
    // 顶点
    GLuint vertexShader = LoadVertexShader(aAssetManager, vertex);
    // 片元
    GLuint fragmentShader = LoadFragmentShader(aAssetManager, fragment);

    // Create the program object
    GLuint programObject = glCreateProgram();

    if (programObject == 0) {
        LOGE("create program is fail");
    }

    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);

    // Link the program
    glLinkProgram(programObject);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Check the link status
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

    if (!linked) {
        GLint infoLen = 0;

        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1) {
            char *infoLog = new char[sizeof(char) * infoLen];
            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
            LOGE("Error linking program : %s", infoLog);
            delete[] infoLog;
        }

        glDeleteProgram(programObject);
        LOGE("CREATE LINK PROGRAM IS FAIL ");
    }

    // Store the program object
    LOGI("CREATE programObject : %d ", programObject);
    return programObject;
}

