package com.example.wzeqiu.myopengles1.es.triangle;

import android.opengl.GLSurfaceView;


import com.example.wzeqiu.myopengles1.es_native.triangle.Native;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

class ESRenderer implements GLSurfaceView.Renderer {
    public ESRenderer() {
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        Native.TriangleInitOpenGL();
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int i, int i1) {
        Native.TriangleOnViewportChanged(i, i1);

    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        Native.TriangleRenderOneFrame();
    }
}
