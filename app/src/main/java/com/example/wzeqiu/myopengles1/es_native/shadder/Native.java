package com.example.wzeqiu.myopengles1.es_native.shadder;


public class Native  {
    
    public static native void ShadderInitOpenGL();

    public static native void ShadderOnViewportChanged(float width, float height);

    public static native void ShadderRenderOneFrame();
}
