#include <jni.h>
#include<android/log.h>
#include<android/asset_manager.h>
#include<android/asset_manager_jni.h>
#include<GLES3/gl3.h>
#include<GLES3/gl3ext.h>

#define TAG "OPENGLES_JNI" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型


GLuint LoadVertexShader(AAssetManager *aAssetManager, const char *filename);

GLuint LoadFragmentShader(AAssetManager *aAssetManager, const char *filename);

GLuint LoadShader(GLenum type, const char *shaderSrc);

char *readShaderBuff(AAssetManager *aAssetManager, const char *name);

/**
 *
 */
GLuint LinkProgram();


AAssetManager *aAssetManager = nullptr;

struct UserData {
    GLuint programObject;
};
UserData *userData = new UserData;


extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_Native_InitAsseManager(JNIEnv *env, jclass type,
                                                                      jobject am) {
    aAssetManager = AAssetManager_fromJava(env, am);
    if (aAssetManager == NULL) {
        LOGE(" InitAsseManager aAssetManager is %s", "aAssetManager==NULL");
        return;
    }
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_Native_InitOpenGL(JNIEnv *env, jclass type) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    GLuint programId = LinkProgram();
    glUseProgram(programId);
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_Native_OnViewportChanged(JNIEnv *env, jclass type,
                                                                        jfloat width,
                                                                        jfloat height) {
    glViewport(0, 0, width, height);

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_Native_RenderOneFrame(JNIEnv *env, jclass type) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat vVertices[] = {0.0f, 0.5f, 0.0f,
                           -0.5f, -0.5f, 0.0f,
                           0.5f, -0.5f, 0.0f
    };

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
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
    LOGI(" asset size        : %d\n", bufferSize);
    char *buffer = new char[bufferSize + 1];
    buffer[bufferSize] = '\0';
    int numByteRead = AAsset_read(asset, buffer, bufferSize);
    LOGI(" numByteRead        : %d\n", numByteRead);
    LOGI(" read buffer is :%s", buffer);
    return buffer;
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

GLuint LinkProgram() {
    GLint linked;
    // Load the vertex/fragment shaders
    // 顶点
    GLuint vertexShader = LoadVertexShader(aAssetManager, "vertex_shader.glsl");
    // 片元
    GLuint fragmentShader = LoadFragmentShader(aAssetManager, "fragment_shader.glsl");

    // Create the program object
    GLuint programObject = glCreateProgram();

    if (programObject == 0) {
        LOGE("create program is fail");
    }

    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);

    // Link the program
    glLinkProgram(programObject);

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
