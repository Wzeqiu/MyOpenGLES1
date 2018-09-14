#include <jni.h>
#include <string>
#include<GLES3/gl3.h>
#include<GLES3/gl3ext.h>
#include<android/asset_manager.h>
#include<android/asset_manager_jni.h>
#include<android/log.h>

#define TAG "OPENGLES_JNI" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型


AAssetManager *aAssetManager = nullptr;

struct UserData{
    GLuint programObject;
} ;
UserData * userData=new UserData;

GLuint LoadShader(GLenum type, const char *shaderSrc) {

    GLuint shader;
    GLint compiled;
    shader = glCreateShader(type);
    if (shader == 0) {
        LOGE("CREATE SHADER IS FAIL TYPE%d", type);
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
            delete[] infoLog;
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;


}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_Native_InitAsseManager(JNIEnv *env, jclass type,
                                                                      jobject am) {
    aAssetManager = AAssetManager_fromJava(env, am);
    // TODO

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_Native_InitOpenGL(JNIEnv *env, jclass type) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    char vShaderStr[] =
            "#version 300 es                          \n"
                    "layout(location = 0) in vec4 vPosition;  \n"
                    "void main()                              \n"
                    "{                                        \n"
                    "   gl_Position = vPosition;              \n"
                    "}                                        \n";

    char fShaderStr[] =
            "#version 300 es                              \n"
                    "precision mediump float;                     \n"
                    "out vec4 fragColor;                          \n"
                    "void main()                                  \n"
                    "{                                            \n"
                    "   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
                    "}                                            \n";

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = LoadShader(GL_VERTEX_SHADER, vShaderStr);
    fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fShaderStr);

    // Create the program object
    programObject = glCreateProgram();

    if (programObject == 0) {
        LOGE("CREATE PROGRAM IS FAIL ");
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
//            esLogMessage ( "Error linking program:\n%s\n", infoLog );

            delete[]  infoLog;
        }

        glDeleteProgram(programObject);
        LOGE("CREATE LINK PROGRAM IS FAIL ");
    }

    // Store the program object
    LOGE("CREATE programObject%d ",programObject);
    userData->programObject = programObject;
    // TODO

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_Native_OnViewportChanged(JNIEnv *env, jclass type,
                                                                        jfloat width,
                                                                        jfloat height) {
    glViewport(0, 0, width, height);

    // TODO

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_wzeqiu_myopengles1_es_1native_Native_RenderOneFrame(JNIEnv *env, jclass type) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat vVertices[] = {0.0f, 0.5f, 0.0f,
                           -0.5f, -0.5f, 0.0f,
                           0.5f, -0.5f, 0.0f
    };

    // Use the program object
    LOGE("RenderOneFrame programObject%d ",userData->programObject);
    glUseProgram(userData->programObject);

    // Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    // TODO

}

