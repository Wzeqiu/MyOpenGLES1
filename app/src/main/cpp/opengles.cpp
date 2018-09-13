#include <jni.h>
#include <string>
#include<GLES3/gl3.h>
#include<GLES3/gl3ext.h>
#include<android/asset_manager.h>
#include<android/asset_manager_jni.h>


AAssetManager *aAssetManager = nullptr;

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

    // TODO

}