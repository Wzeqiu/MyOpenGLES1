package com.example.wzeqiu.myopengles1.es.textures;

import android.opengl.GLSurfaceView;


import com.example.wzeqiu.myopengles1.es_native.textures.Native;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

class ESRenderer implements GLSurfaceView.Renderer {
    public ESRenderer() {
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        Native.TextureInitOpenGL();
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int i, int i1) {
        Native.TextureOnViewportChanged(i, i1);

    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        Native.TextureRenderOneFrame();
    }
}
