package com.example.wzeqiu.myopengles1.es.shadder;

import android.content.Context;
import android.opengl.GLSurfaceView;

public class ESGLSurfaceView extends GLSurfaceView {
    public ESGLSurfaceView(Context context) {
        super(context);
        setEGLContextClientVersion(3);
        setRenderer(new ESRenderer());
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
    }
}
