//
// Created by Wzeqiu on 2018/10/8.
//

#ifndef MYOPENGLES1_GL_UTILS_H

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

GLuint LoadShader(GLenum type, const char *shaderSrc);

char *readShaderBuff(AAssetManager *aAssetManager, const char *name);

GLuint LoadVertexShader(AAssetManager *aAssetManager, const char *filename);

GLuint LoadFragmentShader(AAssetManager *aAssetManager, const char *filename);

GLuint LinkProgram(char *, char *);


#define MYOPENGLES1_GL_UTILS_H


class gl_utils {

};


#endif //MYOPENGLES1_GL_UTILS_H
